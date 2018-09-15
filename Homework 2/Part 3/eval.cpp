#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

int getPrecedence(char o){
    //comparison of precedence where it goes paren, multiply/divide, addition/subtraction
    switch(o){
        case '+':
        case '-':
            return 0;
            break;
        case '*':
        case '/':
            return 1;
            break;
        case '(':
        case ')':
            return 2;
            break;
    }
    return -1;
}

bool precedence(char c1, char c2){
    //+, -, *, and /, parentheses,
    //precedence of c1>=c2)
    return (getPrecedence(c1)>=getPrecedence(c2));
}

bool checkParentheses(string infix){
    stack<char> st;
    for(int i = 0 ; i < infix.length() ; i++){
        if(infix[i] == '('){   //push in stack a left parentheses
            st.push(infix[i]);
        }
        if(infix[i] == ')'){
            if(st.empty()) return false; //search for left parentheses that goes with corresponding right paren
            char ch = st.top();          //pop them off the top and compare
            st.pop();
            if(ch != '(') return false;
        }
    }
    if(st.size() > 0 ) return false;  //if there is a dangling one it will remain after the loop
    return true;
}

bool isValid(string infix){
    string str = "";
    if(infix.length()==0) return false; //check the length 0 case
    //strip the string of whitespaces
    for(int i = 0 ; i < infix.length(); i++){
        if(infix[i]!=' '){
            str+=infix[i];
        }
    }
    if(!islower(str[str.length()-1]) && str[str.length()-1] != ')') return false; //last element is an operator
    if(!islower(str[0]) && str[0]!='(') return false;                             //first element is an operator
    if(!checkParentheses(infix)) return false;
    bool lastNumber = false;
    bool lastOperator = false;
    bool lastRightParen = false;
    bool lastLeftParen = false;
    for(int i = 0; i<str.length();i++){
        switch(str[i]){
            case '+':
            case '-':
            case '*':
            case '/':
                if(lastOperator) return false;  //when there is an operator, the last char cant be operator or left parentheses
                if(lastLeftParen) return false;
                lastRightParen = false;
                lastLeftParen = false;
                lastOperator = true;
                lastNumber = false;
                break;
            case '(':
                if(lastNumber) return false;    //when there is a left paren, the last char can't be a number of right paren
                if(lastRightParen) return false;
                lastLeftParen = true;
                lastRightParen = false;
                lastNumber = false;
                lastOperator = false;
                break;
            case ')':
                if(lastOperator) return false;  //when there is a right paren, the last char cannot be a left paren  or operator
                if(lastLeftParen) return false;
                lastRightParen = true;
                lastLeftParen = false;
                lastOperator = false;
                lastNumber = false;
                break;
            default:
                if(islower(str[i])){   //if it is a number, the last char can't be number or right paren
                    if(lastRightParen) return false;
                    if(lastNumber) return false;
                    lastNumber = true;
                    lastRightParen = false;
                    lastLeftParen = false;
                    lastOperator = false;
                }
                else return 1;  //the character is not valid
        }
    }
    return true;
}
int evaluate(string infix, const Map& values, string& postfix, int& result){
    string p = "";
    stack<char> operations;
    if(!isValid(infix)) return 1; //check if it is valid
    for(int i = 0 ; i < infix.length(); i++){
        switch(infix[i]){
            case '(':  //left paren=>push character in
                operations.push(infix[i]);
                break;
            case ')':
                //right paren, loop until we find the first left paren
                while(!operations.empty() && operations.top()!='('){
                    p+=operations.top();
                    operations.pop();
                    if(operations.empty()) return 1;
                }
                operations.pop();
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                //if it is an operator, we add the corresponding infix
                while(!operations.empty() && operations.top()!='('
                      && precedence(operations.top(), infix[i])){
                    p+=operations.top();
                    operations.pop();
                }
                operations.push(infix[i]);
                break;
            default:
                //if it is a character, we add it to the postfix
                if(islower(infix[i])){
                    p+=infix[i];
                    break;
                }
                else if(infix[i]==' '){
                    break;
                }
        }
        
    }
    //pop out all of the remaining items in the list.
    while(!operations.empty()){
        p+=operations.top();
        operations.pop();
    }
    
    postfix = p;
    stack<int> operand;
    for(int i = 0 ; i< p.size(); i++){
        //if the character is an alphabetic character we convert it to the corresponding number and push it into the evaluation
        if(islower(p[i])){
            int num = 0;
            if(values.get(p[i], num)){
                operand.push(num);
            }
            else{
                return 2;
            }
        }
        else{
            //otherwise it is either a paren or operand
            int operand2 = operand.top();
            operand.pop();
            int operand1 = operand.top();
            operand.pop();
            switch(p[i]){
                //check each of the operations and perform it
                case '*':
                    operand.push(operand1*operand2);
                    break;
                case '/':
                    if(operand2 == 0){
                        return 3;
                    }
                    operand.push(operand1/operand2);
                    break;
                case '+':
                    operand.push(operand1+operand2);
                    break;
                case '-':
                    operand.push(operand1-operand2);
                    break;
            }
        }
    }
    result = operand.top();
    return 0;
}

int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0  &&
           pf == "ae+"  &&  answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
    // unary operators not allowed:
    evaluate("i/u", m, pf, answer);
    assert(answer == 1);
    answer =999;
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
           pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
           pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
           pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    assert(evaluate("(e-i)/(u-y*a)", m, pf, answer)==0);
    assert(evaluate("((a*y)*(u)*(o)*(i+e)))", m, pf, answer) == 1);
    assert(evaluate(")", m, pf, answer)==1);
    assert(evaluate("(", m, pf, answer)==1);
    cout << "Passed all tests" << endl;
}

