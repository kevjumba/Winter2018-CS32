//
//  main.cpp
//  Hwk2 Part3
//
//  Created by Kevin Zhang on 2/4/18.
//  Copyright © 2018 Kevin Zhang. All rights reserved.
//

#include <iostream>
#include "Map.h"
#include <cassert>
#include <stack>
using namespace std;

int getPrecedence(char o){
    switch(o){
        case '+':
        case '-':
            return 0;
        case '*':
        case '/':
            return 1;
    }
    cout<<"something went wrong"<<endl;
    return -1;
}
bool precedence(char c1, char c2){
    //+, -, *, and /, parentheses,
    //precedence of c1>=c2)
    return (getPrecedence(c1)>=getPrecedence(c2));
}

//   Evaluates an integer arithmetic expression
//   If infix is a syntactically valid infix integer expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values map), then postfix is set to the postfix
//   form of the expression; otherwise postfix may or may not be
//   changed, result is unchanged, and the function returns 1.  If
//   infix is syntactically valid but contains at least one lower
//   case letter operand that does not appear in the values map, then
//   result is unchanged and the function returns 2.
//
//If infix is
//   syntactically valid and all its lower case operand letters
//   appear in the values map, then if evaluating the expression
//   (using for each letter in the expression the value in the map
//   that corresponds to it) attempts to divide by zero, then result
//   is unchanged and the function returns 3; otherwise, result is
//   set to the value of the expression and the function returns 0.

int evaluate(string infix, const Map& values, string& postfix, int& result){
    string p = "";
    stack<char> operations;
    if(infix.length() == 0) return 1;
    if(!islower(infix[infix.length()-1]) && infix[infix.length()-1] != ')' && infix[infix.length()-1] != ' ') return 1; //last element is an operator
    if(!islower(infix[0]) && infix[0]!='(' && infix[infix.length()-1] != ' ') return 1;
    bool lastNumber = false;
    bool lastOperator = false;
    bool lastLeftParentheses = false;
    bool lastRightParentheses = false;
    for(int i = 0 ; i < infix.length(); i++){
        switch(infix[i]){
            case '(':
                operations.push(infix[i]);
                if(lastNumber) return 1;
                if(lastRightParentheses) return 1;
                lastRightParentheses = false;
                lastLeftParentheses = true;
                lastNumber = false;
                lastOperator = false;
                break;
            case ')':
                if(lastLeftParentheses){
                    return 1;
                }
                lastRightParentheses = true;
                lastLeftParentheses = false;
                lastNumber = false;
                lastOperator = false;
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
                
                if(lastOperator){
                    return 1;
                }
                lastLeftParentheses = false;
                lastRightParentheses = false;
                lastNumber = false;
                lastOperator = true;
                while(!operations.empty() && operations.top()!='('
                      && precedence(operations.top(), infix[i])){
                    p+=operations.top();
                    operations.pop();
                }
                operations.push(infix[i]);
                break;
            default:
                if(islower(infix[i])){
                    if(lastNumber) return 1;
                    lastNumber = true;
                    lastOperator = false;
                    lastLeftParentheses = false;
                    lastRightParentheses = false;
                    p+=infix[i];
                    break;
                }
                else if(infix[i]==' '){
                    break;
                }
                else{
                    return 1;
                }
        }
        
    }
    while(!operations.empty()){
        p+=operations.top();
        operations.pop();
    }
    if(p[p.length()-1] == '(') return 1;
    postfix = p;
    stack<int> operand;
    for(int i = 0 ; i< p.size(); i++){
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
            int operand2 = operand.top();
            operand.pop();
            int operand1 = operand.top();
            operand.pop();
            switch(p[i]){
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
    postfix = p;
    result = operand.top();
    return 0;
}
// Evaluates an integer arithmetic expression
//   If infix is a syntactically valid infix integer expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values map), then postfix is set to the postfix
//   form of the expression; otherwise postfix may or may not be
//   changed, result is unchanged, and the function returns 1.  If
//   infix is syntactically valid but contains at least one lower
//   case letter operand that does not appear in the values map, then
//   result is unchanged and the function returns 2.  If infix is
//   syntactically valid and all its lower case operand letters
//   appear in the values map, then if evaluating the expression
//   (using for each letter in the expression the value in the map
//   that corresponds to it) attempts to divide by zero, then result
//   is unchanged and the function returns 3; otherwise, result is
//   set to the value of the expression and the function returns 0.
/*
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
    cout << "Passed all tests" << endl;
}*/
