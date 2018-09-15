// Map.cpp
#include <iostream>
using namespace std;
#include "Map.h"

struct Node;

Map::Map()
: m_size(0)
{
    head = nullptr;
    tail = nullptr;
}

bool Map::empty() const{
    return (m_size==0);
}

int Map::size() const{
    return m_size;
}

Map::Map(const Map & other){
    Node * node = other.head;
    head = nullptr;
    tail = nullptr;
    while(node!=nullptr){
        insert(node->pair.m_key, node->pair.m_value);
        node = node->next;
    }
}
Map& Map::operator=(const Map &other)
{
    if(&other == this){
        return (*this);
    }
    Node * it = head;
    while(it!=nullptr){
        Node * temp = it;
        it = it->next;
        m_size--;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    Node * node = other.head;
    while(node!=nullptr){
        insert(node->pair.m_key, node->pair.m_value);
        node = node->next;
    }
    return (*this);
}

bool Map::insert(const KeyType& key, const ValueType& value){
    // Do a linear search through the array.
    
    if(head == nullptr){
        Node * node;
        node = new Node;
        node->pair.m_key = key;
        node->pair.m_value = value;
        head = node;
        tail = node;
        head->prev = nullptr;
        head->next = nullptr;
        tail->prev = nullptr;
        tail->next = nullptr;
        m_size++;
        return true;
    }
    //search for the value
    Node * p = head;
    while(p!=nullptr){
        if(p->pair.m_key == key){
            return false;
        }
        p = p->next;
    }
    //insert at the end of linked list
    
    Node * node;
    node = new Node;
    node->pair.m_key = key;
    node->pair.m_value = value;
    node->prev = tail;
    node->next = nullptr;
    tail->next = node;
    tail = node;
    m_size++;
    return true;
    
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    Node * node = head;
    while(node!=nullptr){
        if(node->pair.m_key == key){
            node->pair.m_value = value;
            return true;
        }
        node = node->next;
    }
    return insert(key, value);
}

bool Map::erase(const KeyType& key)
{
    Node * node = head;
    while(node!=nullptr){
        if(node->pair.m_key == key){
            break;
        }
        node = node->next;
    }
    if (node == nullptr)  // not found
        return false;
    
    m_size--;
    if(node == head && node == tail){
        head = nullptr;
        tail = nullptr;
    }
    else if(node == head){
        head = node->next;
        head->prev = nullptr;
    }
    else if(node == tail){
        tail = node->prev;
        tail->next = nullptr;
    }
    else{
        node->prev->next = node->next;
        node->next->prev = node->prev;
        
    }
    delete node;
    return true;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    Node * node = head;
    while(node!=nullptr){
        if(node->pair.m_key == key){
            break;
        }
        node = node->next;
    }
    if (node == nullptr)  // not found
        return false;
    value = node->pair.m_value;
    return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i < 0  ||  i >= m_size || head == nullptr)
        return false;
    Node * temp = head;
    for(int j = 0; j < i ; j++){
        temp = temp->next;
    }
    key = temp->pair.m_key;
    value = temp->pair.m_value;
    return true;
}

void Map::swap(Map& other)
{
    
    Map tempMap = other;
    other = *this;
    *this = tempMap;
    
}

bool Map::update(const KeyType& key, const ValueType& value){
    Node * node = head;
    while(node!=nullptr){
        if(node->pair.m_key == key){
            node->pair.m_value = value;
            return true;
        }
        node = node->next;
    }
    return false;
}

bool Map::contains(const KeyType& key) const{
    Node * node = head;
    while(node!=nullptr){
        if(node->pair.m_key == key){
            return true;
        }
        node = node->next;
    }
    return false;
}
void Map::dump() const{
    Node * node = head;
    while(node != nullptr){
        cerr<<node->pair.m_key<<" "<<node->pair.m_value<<endl;
        node = node->next;
    }
}

Map::~Map(){
    Node * it = head;
    while(it!=nullptr){
        Node * temp = it;
        it = it->next;
        delete temp;
    }
}
/*
 When this function returns, result must consist of pairs determined by these rules:
 
 If a key appears in exactly one of m1 and m2, then result must contain a pair consisting of that key and its corresponding value.
 If a key appears in both m1 and m2, with the same corresponding value in both, then result must contain exactly one pair with that key and value.
 When this function returns, result must contain no pairs other than those required by these rules. (You must not assume result is empty when it is passed in to this function; it might not be.)
 
 If there exists a key that appears in both m1 and m2, but with different corresponding values, then this function returns false; if there is no key like this, the function returns true. Even if the function returns false, result must be constituted as defined by the above rules.
 */
bool combine(const Map& m1, const Map& m2, Map& result){
    Map newMap;
    result = newMap;
    bool ret = true;
    for(int i = 0; i< m1.size(); i++){
        KeyType key;
        ValueType value;
        m1.get(i, key, value);
        ValueType val2;
        bool res = m2.get(key, val2);
        if(res){
            if(val2 == value){
                result.insert(key, value);
            }
            else{
                ret = false;
            }
        }
        else{
            result.insert(key, value);
        }
    }
    
    for(int i = 0; i < m2.size(); i++){
        KeyType key;
        ValueType value;
        m2.get(i, key, value);
        ValueType val2;
        bool res = m1.get(key, val2);
        if(res){
            if(val2 == value){
                if(!result.contains(key)){
                    result.insert(key, value);
                }
            }
            else{
                ret = false;
            }
        }
        else{
            result.insert(key, value);
        }
    }
    
    return ret;
}
/*
 When this function returns, result must contain one copy of all the pairs in m1 whose keys don't appear in m2; it must not contain any other pairs. (You must not assume result is empty when it is passed in to this function; it may not be.)*/
void subtract(const Map& m1, const Map& m2, Map& result){
    Map newMap;
    result = newMap;
    for(int i = 0; i< m1.size();i++){
        KeyType key;
        ValueType value;
        m1.get(i, key, value);
        if(!m2.contains(key)){
            result.insert(key, value);
        }
    }
    
}
