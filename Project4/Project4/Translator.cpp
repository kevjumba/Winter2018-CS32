#include "provided.h"
#include <string>
#include "MyHash.h"
#include <cctype>
using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
    ~TranslatorImpl();
private:
    vector<char *> mapFragments;
    vector<char *> alreadyMappedRecords;
    char * currentMapping;
    char * alreadyMapped;
};

TranslatorImpl::TranslatorImpl(){
    currentMapping = new char[26];
    alreadyMapped = new char[26];
    //initialize the current mappings to ? since nothing has happened
    for(int i = 0; i < 26; i++){
        currentMapping[i] = '?';
        alreadyMapped[i] = '?';
    }
}

TranslatorImpl::~TranslatorImpl(){
    //to deconstruct we need to delete all of the array elements
    for(int i =0 ; i < mapFragments.size(); i++){
        delete mapFragments[i];
    }
    //to deconstruct we need to delete all of the mapped elements
    for(int i =0 ; i < alreadyMappedRecords.size(); i++){
        delete alreadyMappedRecords[i];
    }
    //delete the array memory space
    delete [] currentMapping;
    delete [] alreadyMapped;
}
bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    //if ciphertext and plaintext is equal
    if(ciphertext.size() != plaintext.size()) return false;
    //if either contains a non-letter, or if the new
    //    character mappings they specify, together with the current collection of character
    //    mappings, would be inconsistent,
    
    //initialize a cipher and plain text temporary mapping that contains the pushed mappings one by one
    //this is the make sure we catch errors like DDE => XAG b/c this maps D to X and A but we can't do this
    //in the actual updating loop since we want the function to return false before updating
    char cipher[26];
    char plain[26];
    //set it all to a default character
    for(int i = 0 ; i < 26; i++){
        cipher[i] = '0';
        plain[i] = '0';
    }
    for(int i = 0; i < ciphertext.size(); i++){
        //if it's either string is not alphabetic return
        if(!isalpha(ciphertext[i])||!isalpha(plaintext[i])){
            return false;
        }
        //if the cipher text letter is mapping to two plain text letters return false
        if(cipher[tolower(ciphertext[i])-'a'] != '0' && cipher[tolower(ciphertext[i])-'a'] != tolower(plaintext[i])){
            return false;
        }
        //if the plain text letter is mapped to by two cipher text letters return false
        if(plain[tolower(plaintext[i])-'a'] != '0' && plain[tolower(plaintext[i])-'a'] != tolower(ciphertext[i])){
            return false;
        }
        
        //add the letters to the temp arrays
        cipher[tolower(ciphertext[i])-'a'] = tolower(plaintext[i]);
        plain[tolower(plaintext[i])-'a'] = tolower(ciphertext[i]);
        
        char c = currentMapping[tolower(ciphertext[i])-'a'];
        char a = alreadyMapped[tolower(plaintext[i])-'a'];
        //if the cipher text letter is mapping to already by another plain text letter return false
        if(c!='?'&&c!=tolower(plaintext[i])) {
            return false;
        }
        //if the plain text letter is mapped to by another cipher text letter return false

        if(a!='?' && a != tolower(ciphertext[i])) {
            return false;
        }
    }
    
    //there is no invalid mappings occuring, create new previous mappings and copy all of the current mappings into them
    char * prevMapping = new char[26];
    char * prevRecord = new char[26];
    for(int i = 0; i < 26; i++){
        prevMapping[i] = currentMapping[i];
        prevRecord[i] = alreadyMapped[i];
    }
    
    //push it into the stack
    alreadyMappedRecords.push_back(prevRecord);
    mapFragments.push_back(prevMapping);
    
    //now we go through the mapping and update the ones that are unkown
    for(int i = 0; i < ciphertext.size(); i++){
	    if(currentMapping[tolower(ciphertext[i])-'a'] == '?'){
		  currentMapping[tolower(ciphertext[i])-'a'] = tolower(plaintext[i]);
        }
        if(alreadyMapped[tolower(plaintext[i])-'a'] == '?'){
		  alreadyMapped[tolower(plaintext[i])-'a'] = tolower(ciphertext[i]);

        }
    }
    return true;
}

bool TranslatorImpl::popMapping()
{
    //if there are no more map fragments return false
    if(mapFragments.size()<=0) return false;
    //get the top mapping in the stack
    char * lastMapping = mapFragments.back();
    char * lastAlreadyMapped =alreadyMappedRecords.back();
    mapFragments.pop_back();
    alreadyMappedRecords.pop_back();
    
    //pop the last mapping
    //copy this popped mapping into the current mappings
    for(int i = 0; i < 26; i++){
        alreadyMapped[i] = lastAlreadyMapped[i];
        currentMapping[i] = lastMapping[i];
    }
    
    //delete the array space used by that stack item
	delete [] lastAlreadyMapped;
    delete [] lastMapping;
	return true;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    string translated = "";
    //loop through ciphertext
    for(int i = 0; i < ciphertext.size(); i++){
        //if isn't an alphabetic character, just add it to the translation and continue
        if(!isalpha(ciphertext[i])){
            translated+=ciphertext[i];
            continue;
        }
        //if it is an alphabetic character grab the corresponding character from the list.
        char c = currentMapping[tolower(ciphertext[i])-'a'];
        if(isupper(ciphertext[i])){
		    c = toupper(c);
		}
        //change it to upper if necessary and use it.
		translated += c;
    }
    return translated; // This compiles, but may not be correct
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
