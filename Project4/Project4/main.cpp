// Coming soon

#include <iostream>
#include "provided.h"
#include <ctime>
#include "MyHash.h"
using namespace std;


int main()
{
    std::clock_t start;
    double duration;
    ///WordList w;
    //w.loadWordList("/Users/kevinzhang/Documents/CS/32/Project4/Project4/wordlist.txt");
    //vector<string> g = w.findCandidates("won't", "?????");
    //Tokenizer t(" ,;:.!()[]{}-\"#$%^&1234567890");
    start = std::clock();
    Decrypter d;
    d.load("/Users/kevinzhang/Documents/CS/32/Project4/Project4/wordlist.txt");
    string str4 =  "y qook ra bdttook yqkook.";
    string str5 =  " Xjzwq gjz cuvq xz huri arwqvudiy fuk ufjrqoq svquxiy. -Lzjk Nqkkqcy ";
    string str6 = "Lzdkgd dyrmjls shcg xdggkud fpm xd!!";
    string str =  "Trcy oyc koon oz rweelycbb vmobcb, wyogrcn oecyb; hjg ozgcy tc moox bo moya wg grc vmobck koon grwg tc ko yog bcc grc oyc trlvr rwb hccy oecyck zon jb. -Rcmcy Xcmmcn";
    string str1 = "Jxwpjq qwrla glcu pcx qcn xkvv dw uclw ekarbbckpjwe dq jzw jzkpta jzrj qcn ekep'j ec jzrp dq jzw cpwa qcn eke ec. -Urls Jxrkp";
    string str2 = "I vle'a";
    //string str3 ="Qc wacp'n nlc hpcg qlh qtp, qc wac nlc hpcg qlh bcgnahv.";
    vector<string> v = d.crack(str);
    //cout<<"Original Message: "<<"Lzdkgd dyrmjls shcg xdggkud fpm xd!!"<<endl<<endl;
    cout<<"Original Message: "<<str<<endl<<endl;
    cout<<"Decrypted: "<<endl;
    for(int i = 0; i < v.size(); i++){
        cout<<v[i]<<endl;
    }
    cout<<endl;
    v = d.crack(str1);
    //cout<<"Original Message: "<<"Lzdkgd dyrmjls shcg xdggkud fpm xd!!"<<endl<<endl;
    cout<<"Original Message: "<<str<<endl<<endl;
    cout<<"Decrypted: "<<endl;
    for(int i = 0; i < v.size(); i++){
        cout<<v[i]<<endl;
    }
    cout<<endl;
    v = d.crack(str2);
    //cout<<"Original Message: "<<"Lzdkgd dyrmjls shcg xdggkud fpm xd!!"<<endl<<endl;
    cout<<"Original Message: "<<str2<<endl<<endl;
    cout<<"Decrypted: "<<endl;
    for(int i = 0; i < v.size(); i++){
        cout<<v[i]<<endl;
    }
    cout<<endl;
    v = d.crack(str4);
    //cout<<"Original Message: "<<"Lzdkgd dyrmjls shcg xdggkud fpm xd!!"<<endl<<endl;
    cout<<"Original Message: "<<str4<<endl<<endl;
    cout<<"Decrypted: "<<endl;
    for(int i = 0; i < v.size(); i++){
        cout<<v[i]<<endl;
    }
    v = d.crack(str5);
    //cout<<"Original Message: "<<"Lzdkgd dyrmjls shcg xdggkud fpm xd!!"<<endl<<endl;
    cout<<"Original Message: "<<str5<<endl<<endl;
    cout<<"Decrypted: "<<endl;
    for(int i = 0; i < v.size(); i++){
        cout<<v[i]<<endl;
    }
    cout<<endl;
    v = d.crack(str6);
    //cout<<"Original Message: "<<"Lzdkgd dyrmjls shcg xdggkud fpm xd!!"<<endl<<endl;
    cout<<"Original Message: "<<str6<<endl<<endl;
    cout<<"Decrypted: "<<endl;
    for(int i = 0; i < v.size(); i++){
        cout<<v[i]<<endl;
    }
    cout<<endl;
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<<duration<<endl;
}

/*
 Axevfvu lvnelvp bxqp mvpprjv rgl bvoop Grnxvgkvuj dqupb jvbp buvrbvl be lqggvu.
 Xjzwq gjz cuvq xz huri arwqvudiy fuk ufjrqoq svquxiy. -Lzjk Nqkkqcy
 Jxwpjq qwrla glcu pcx qcn xkvv dw uclw ekarbbckpjwe dq jzw jzkpta jzrj qcn ekep'j ec jzrp dq jzw cpwa qcn eke ec. -Urls Jxrkp
 Trcy oyc koon oz rweelycbb vmobcb, wyogrcn oecyb; hjg ozgcy tc moox bo moya wg grc vmobck koon grwg tc ko yog bcc grc oyc trlvr rwb hccy oecyck zon jb. -Rcmcy Xcmmcn
 */
/*
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
#include <random>
#include <algorithm>
#include <numeric>
using namespace std;

const string WORDLIST_FILE = "/Users/kevinzhang/Documents/CS/32/Project4/Project4/wordlist.txt";

string encrypt(string plaintext)
{
    // Generate a to z
    char plaintextAlphabet[26+1];
    iota(plaintextAlphabet, plaintextAlphabet+26, 'a');
    plaintextAlphabet[26] = '\0';
    
    // Generate permutation
    string ciphertextAlphabet(plaintextAlphabet);
    default_random_engine e((random_device()()));
    shuffle(ciphertextAlphabet.begin(), ciphertextAlphabet.end(), e);
    
    // Run translator (opposite to the intended direction)
    Translator t;
    t.pushMapping(plaintextAlphabet, ciphertextAlphabet);
    return t.getTranslation(plaintext);
}

bool decrypt(string ciphertext)
{
    Decrypter d;
    if ( ! d.load(WORDLIST_FILE))
    {
        cout << "Unable to load word list file " << WORDLIST_FILE << endl;
        return false;
    }
    for (const auto& s : d.crack(ciphertext))
        cout << s << endl;
    return true;
}

int main(int argc, char* argv[])
{
    if (argc == 3  &&  argv[1][0] == '-')
    {
        switch (tolower(argv[1][1]))
        {
            case 'e':
                cout << encrypt(argv[2]) << endl;
                return 0;
            case 'd':
                if (decrypt(argv[2]))
                    return 0;
                return 1;
        }
    }
    
    cout << "Usage to encrypt:  " << argv[0] << " -e \"Your message here.\"" << endl;
    cout << "Usage to decrypt:  " << argv[0] << " -d \"Uwey tirrboi miyi.\"" << endl;
    return 1;
}

*/
