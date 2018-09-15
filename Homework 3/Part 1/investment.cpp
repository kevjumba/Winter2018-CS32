#include <iostream>
#include <string>
using namespace std;

class Investment {
public:
    Investment(string name, int value);
    string name() const;
    virtual bool fungible() const = 0;
    virtual string description() const = 0;
    virtual ~Investment(){}
    int purchasePrice() const;
private:
    string m_name;
    int m_value;
};

Investment::Investment(string name, int value){
    m_name = name;
    m_value = value;
}

string Investment::name() const{
    return m_name;
}
int Investment::purchasePrice() const{
    return m_value;
}
class Painting : public Investment{
public:
    Painting(string name, int value):Investment(name, value){}
    virtual bool fungible() const;
    virtual string description() const;
    virtual ~Painting();
};

bool Painting::fungible() const{
    return false;
}

string Painting::description() const{
    return "painting";
}

Painting::~Painting(){
    cout<<"Destroying "<<name()<<", a painting"<<endl;
}

class Stock : public Investment {
public:
    Stock(string name, int value, string ticker) : Investment(name, value){
        m_ticker = ticker;
    }
    virtual bool fungible() const;
    virtual string description() const;
    virtual ~Stock();
    
private:
    string m_ticker;
};

bool Stock::fungible() const{
    return true;
}
string Stock::description() const{
    return ("stock trading as " + m_ticker);
}
Stock::~Stock(){
    cout<<"Destroying "<<name()<<", a stock holding"<<endl;
}

class House : public Investment {
public:
    House(string name, int value) : Investment(name, value){}
    virtual bool fungible() const;
    virtual string description() const;
    virtual ~House();
};

bool House::fungible() const{
    return false;
}
string House::description() const{
    return "house";
}
House::~House(){
    cout<<"Destroying the house "<<name()<<endl;
}

void display(const Investment* inv)
{
    cout << inv->name();
    if (inv->fungible())
        cout << " (fungible)";
    cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
}

int main()
{
    Investment* portfolio[4];
    portfolio[0] = new Painting("Salvator Mundi", 450300000);
    // Stock holdings have a name, value, and ticker symbol
    portfolio[1] = new Stock("Alphabet", 100000, "GOOGL");
    portfolio[2] = new Stock("Symantec", 50000, "SYMC");
    portfolio[3] = new House("4 Privet Drive", 660000);
    
    for (int k = 0; k < 4; k++)
        display(portfolio[k]);
    
    // Clean up the investments before exiting
    cout << "Cleaning up" << endl;
    for (int k = 0; k < 4; k++)
        delete portfolio[k];
}

/*
 Salvator Mundi: painting bought for $450300000
 Alphabet (fungible): stock trading as GOOGL bought for $100000
 Symantec (fungible): stock trading as SYMC bought for $50000
 4 Privet Drive: house bought for $660000
 Cleaning up
 Destroying Salvator Mundi, a painting
 Destroying Alphabet, a stock holding
 Destroying Symantec, a stock holding
 Destroying the house 4 Privet Drive
 */
