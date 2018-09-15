#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
using namespace std;

class DecrypterImpl
{
public:
    DecrypterImpl() : tok(" ,;:.!()[]{}-\"#$%^&1234567890") {}
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
    ~DecrypterImpl(){};
private:
    WordList w;
    Tokenizer tok;
    Translator t;
    string currentString;
    void Crack(string ciphertext_message, string translated_message, vector<string>& output);
};

bool DecrypterImpl::load(string filename)
{
    return w.loadWordList(filename);
}

void DecrypterImpl::Crack(string ciphertext_message, string translated_message, vector<string>& output){
    //first tokenize both messages into vectors of strings
    vector<string> translatedWords = tok.tokenize(translated_message);
    vector<string> words = tok.tokenize(ciphertext_message);
    string word = "";
    int maxUnknown = -1;
    int index = 0;
    //find a word in the current message list with the largest number of unknowns
    for(int i = 0; i < translatedWords.size(); i++){
        int sum = 0;
        for(int j = 0; j < translatedWords[i].size(); j++){
            if(translatedWords[i][j]=='?'){
                sum++;
            }
        }
        if(sum>=maxUnknown){
            maxUnknown = sum;
            word = words[i];
            index = i;
        }
    }
    //find the words with this particular word's pattern and translated matching
    vector<string> matches = w.findCandidates(word, translatedWords[index]);
    //if the matches are empty, that means that there are no words that match
    if(matches.empty()){
        //pop the current non working mapping and return.
        t.popMapping();
        return;
    }
    for(int i = 0; i < matches.size(); i++){
        //get a temporary string for translation and cipher
        string translated_str;
        string word_str;
        //loop through each and make sure it doesn't contain any nonalphabetic chars
        for(int j = 0; j < matches[i].size(); j++){
            if(isalpha(matches[i][j])){
                translated_str+=matches[i][j];
            }
        }
        for(int j = 0; j < word.size(); j++){
            if(isalpha(word[j])){
                word_str+=word[j];
            }
        }
        //push mapping with the current mapping
        //if it isn't a valid one just continue to the next loop
        if(!t.pushMapping(word_str, translated_str)){
            continue;
        }
        //find the message created by this translation
        string newMessage = t.getTranslation(ciphertext_message);
        vector<string> newWords = tok.tokenize(newMessage);
        if(newMessage.find('?')==string::npos){
            //this means everything is decoded
            bool isValid = true;
            //for each new Word, check all of the words to see if any are not valid
            for(int i = 0; i < newWords.size(); i++){
                if(!w.contains(newWords[i])){
                    //if we find invalid word, we pop the current mapping and break
                    t.popMapping();
                    isValid = false;
                    break;
                }
            }
            //if there was a good mapping, push the output to the list of strings and pop
            if(isValid){
                output.push_back(newMessage);
                t.popMapping();
            }
            continue;
        }
        //this means there are still unknowns so first I check all fully decrypted words
        bool valid = true;
        for(int i = 0; i < newWords.size(); i++){
            bool hasUnknown = false;
            for(int j = 0; j < newWords[i].size(); j++){
                //if it has '?' it is still unknown
                if(newWords[i][j] == '?'){
                    hasUnknown = true;
                }
            }
            //if it is not unknown check if it is a valid word
            if(!hasUnknown){
                if(!w.contains(newWords[i])){
                    valid = false;
                    break;
                }
            }
        }
        //if everything is valid, recurse and crack it with the new message
        if(valid){
            //all fully translated words are valid
            Crack(ciphertext_message, newMessage, output);
        }
        //else just pop the mapping
        else{
            t.popMapping();
        }
    }
    //at the end of each loop pop the current mapping
    t.popMapping();
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    //copy the ciphertext to a temporary string
    currentString = ciphertext;
    string newString = ciphertext;
    //create a new temporary string that is the lowercase version of that string
    for(int i = 0; i < newString.size(); i++){
        newString[i] = tolower(newString[i]);
    }
    vector<string> output;
    string unknown = "";
    //create a string of unkowns
    for(int i = 0;i < ciphertext.size(); i++){
        if(isalpha(ciphertext[i])){
            unknown+="?";
        }
        else{
            unknown+=ciphertext[i];
        }
    }
    //start the translation with ciphertext and "??????"
    Crack(newString, unknown, output);
    //now go through the output vector and make the case the same as the original cipher text
    for(int i = 0; i < output.size(); i++){
        for(int j = 0; j < output[i].size(); j++){
            if(isupper(currentString[j])){
                output[i][j] = toupper(output[i][j]);
            }
        }
    }
    //sort the vector
    std::sort(output.begin(), output.end());
    return output;
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
