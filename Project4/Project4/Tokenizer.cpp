#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "provided.h"

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const std::string& s) const;
    ~TokenizerImpl(){};
private:
    string m_separators;
};

TokenizerImpl::TokenizerImpl(string separators)
{
    m_separators = separators;
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
    //initialize a vector of strings
    vector<string> v;
    string tmp = "";
    for(int i = 0; i < s.size(); i++){
        bool separated = false;
        //for each character in the string
        for (int j = 0; j < m_separators.size(); j++) {
            //loop through all the separators and see if there is a match
            //if it is a separator, push the tmp string into the vector
            if(s[i] == m_separators[j]){
                separated = true;
                if(tmp == ""){
                    break;
                }
                v.push_back(tmp);
                tmp = "";
                break;
            }
        }
        //else just continue adding character to the tmp string
        if(!separated){
            tmp+=s[i];
        }
    }
    //if there is no space at the end, tmp won't be pushed so push it here
    if(tmp.size()>0){
        v.push_back(tmp);
    }
    return v;
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}
