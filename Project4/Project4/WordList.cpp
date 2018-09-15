
#include <stdio.h>
#include <iostream>
#include <vector>
#include "stdlib.h"
#include "MyHash.h"
#include <algorithm>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class WordListImpl
{
public:
    WordListImpl(){};
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
    ~WordListImpl(){};
private:
    MyHash<string, string> wordList;
    MyHash<string, vector<string>> index_pattern;
    string getPattern(string s) const;
};

string WordListImpl::getPattern(string s) const{
    string a;
    int arr[26];
    //initialize a temp array to -1s
    for(int i = 0; i < 26; i++){
        arr[i] = -1;
    }
    int j = 0;
    //characters is all the symbols we'll be using
    string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i = 0; i < s.size(); i++){
        //for every letter in s, if it is not alphabetic just add it to the pattern
        if(!isalpha(s[i])){
            a+=s[i];
            continue;
        }
        //if there is not a mapping for that array
        if(arr[tolower(s[i])-'a'] == -1){
            //add the mapping to the character array
            a+=characters[j];
            arr[tolower(s[i])-'a'] = j;
            //increment the integer of the first not used symbol
            j++;
        }
        //if it already mapped, just add the corresponding letter to the pattern
        else{
		  a+=characters[arr[tolower(s[i])-'a']];
        }
    }
    //return the pattern
    return a;
}

bool WordListImpl::loadWordList(string filename)
{
    //reset hashmaps in wordList
    wordList.reset();
    index_pattern.reset();
    ifstream fin(filename);
    if (fin.is_open())
    {
        //if the stream if open
        string line;
        //getline until I can't
        while ( getline (fin,line) )
        {
            //make sure everything is within the valid character range and is lower case
            for(int i = 0 ; i < line.size(); i++){
                if(line[i]!='\'' && !isalpha(line[i])){
                    continue;
                }
                if(isupper(line[i])){
                    line[i] = tolower(line[i]);
                }
            }
            //if i cant find it in the wordlist continue
            if(wordList.find(line)!=nullptr){
                continue;
            }
            //grab the pattern and associate the word with the word
            string pattern = getPattern(line);
            wordList.associate(line, line);
			vector<string> * ptr = index_pattern.find(pattern);
            if(!ptr){
                //add a new vector and associate the new one
                vector<string > v;
                v.push_back(line);
                index_pattern.associate(getPattern(line), v);
            }
            else{
                //if there is already the pattern in the map, add the line to that vector
			  ptr->push_back(line);
            }
        }
        //close the file and return true
        fin.close();
        return true;
        
    }
    //if it can't open return false
    else {
        return false;
    }
}

bool WordListImpl::contains(string word) const
{
    //NOTE Case insensitive
    //transform the word to lower
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    //check the if word is in the wordList
    return (wordList.find(word) != nullptr);
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    //first try to find the pattern
    vector<string> answer;
    const vector<string> * v = index_pattern.find(getPattern(cipherWord));
    //if it is not in the list or the cipherword and currtranslation are equal return answer
    if(v == nullptr || cipherWord.size() != currTranslation.size())
        return answer;
    //loop through the currtranslation and make sure it is valid
    for(int i = 0; i < currTranslation.size(); i++){
        if(!isalpha(cipherWord[i]) && cipherWord[i] != '\''){
            return answer;
        }
        if(!isalpha(currTranslation[i]) && currTranslation[i]!='?' && currTranslation[i]!='\'' ){
            return answer;
        }
    }
    
    //go through the vector and filter out the strings that conflict with the translation string
    for(int i = 0; i < (*v).size(); i++){
        string tmp = ((*v)[i]);
        bool add = true;
        for(int j = 0; j < tmp.size(); j++){
            if(currTranslation[j]=='?'){
                continue;
            }
            else if(tolower(tmp[j])!=tolower(currTranslation[j])){
                add = false;
                break;
            }
        }
        if(add){
            answer.push_back(tmp);
        }
    }
    //return the answer vector
    return answer;
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

 unsigned int hash(const int& i)
 {
 return std::hash<int>()(i);
 }
 
 unsigned int hash(const char& c)
 {
 return std::hash<char>()(c);
 }

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
    return m_impl->findCandidates(cipherWord, currTranslation);
}
