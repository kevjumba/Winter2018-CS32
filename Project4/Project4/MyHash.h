//
//  MyHash.hpp
//  Project4
//
//  Created by Kevin Zhang on 3/7/18.
//  Copyright © 2018 Kevin Zhang. All rights reserved.
//

#ifndef MyHash_h
#define MyHash_h

#include <iostream>
#include <vector>
#include <list>

template <class KeyType, class ValueType>
struct Node{
    KeyType key;
    ValueType value;
    Node<KeyType, ValueType> * next;
    Node(KeyType k, ValueType v): key(k), value(v) {}
};

template <class KeyType, class ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5){
        //set maxLoad factor to a reasonable range
        if (maxLoadFactor <= 0) m_maxLoadFactor = 0.5;
        else if(maxLoadFactor > 2) m_maxLoadFactor = 2;
        else{
            m_maxLoadFactor = maxLoadFactor;
        }
        //initialize map to a new 100 space
        m_map = new Node<KeyType, ValueType> * [100];
        m_elements = 0;
        m_capacity = 100;
        //for every element initialize the linked list to empty
        for(int i = 0; i < m_capacity; i++){
            (m_map)[i] = nullptr;
        }
    }
    ~MyHash();
    void reset();
    const ValueType* find(const KeyType& key) const;
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const;
    double getLoadFactor() const;
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;
private:
    double m_maxLoadFactor;
    Node<KeyType, ValueType> ** m_map;
    int m_elements;
    int m_capacity;
    void insert(KeyType key, ValueType value, int index);
    
};

template<class KeyType, class ValueType>
inline
void MyHash<KeyType, ValueType>::insert(KeyType key, ValueType value, int index){
    //increment the number of elements
    m_elements++;
    //get the head of the corresponding index
    Node<KeyType, ValueType> * head = m_map[index];
    //create a new Node
    Node<KeyType, ValueType> * insert = new Node<KeyType, ValueType>(key, value);
    //if the linked list is null, just add the node
    if(head == nullptr){
        m_map[index] = insert;
        insert->next = nullptr;
    }
    //if the linked list is not null, just add the node to the front
    else{
        insert->next = head;
        m_map[index] = insert;
    }
}

template<class KeyType, class ValueType>
inline
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value){
    unsigned int hash(const KeyType& k); // prototype
    
    //try to find the key in the map
    ValueType * v = find(key);
    //if found, then update value
    if(v != nullptr){
        *v = value;
    }
    //else not found
    else{
        //get a new index
        unsigned int index = hash(key)%m_capacity;
        //insert the key and value into the list
        insert(key, value, index);
        //if this insert makes the load factor overflow
        if(getLoadFactor()>m_maxLoadFactor){
            //reset the m_elements to 0 so that inserting will cause m_elements to reset
		    m_elements=0;
            //initialize new pointer to old memory space
            Node<KeyType, ValueType> ** oldMap = m_map;
            //reinitialize the m_map pointer to a new memory space with 2 * m_capacity
            m_map = new Node<KeyType, ValueType> * [m_capacity*2];
            for(int i = 0; i < m_capacity * 2; i++){
                //set all of this space to nullptr
                m_map[i]= nullptr;
            }
            
            for(int i = 0 ; i < m_capacity; i++){
                //for everything in the original map, insert the node at the correct place
                Node<KeyType, ValueType> * node = oldMap[i];
                if(node == nullptr){
                    continue;
                }
                else{
                    while(node!=nullptr){
                        int newIndex =hash(node->key)%(2*m_capacity);
                        //int newIndex = std::hash<KeyType>()(node->key)%(2*m_capacity);
                        Node<KeyType, ValueType> * tmp = node;
                        insert(node->key, node->value, newIndex);
                        node = node->next;
                        //delete the original node
                        delete tmp;
                    }
                }
            }
            //delete the original mapping
            delete [] oldMap;
            m_capacity*=2;
			}
    }
}
template<class KeyType, class ValueType>
inline
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const{
    unsigned int hash(const KeyType& k); // prototype
    //get the index from the key
    unsigned int index = hash(key)%m_capacity;
    //get the head
    Node<KeyType, ValueType> * head = m_map[index];
    //loop through the linked list rooted at head and try to find the key
    while(head != nullptr){
        if(head->key == key){
            return &head->value;
        }
        head = head->next;
    }
    //if key isn't there, return nullptr
    return nullptr;
}

template<class KeyType, class ValueType>
inline
int MyHash<KeyType, ValueType>::getNumItems() const{
    return m_elements;
}

template<class KeyType, class ValueType>
inline
double MyHash<KeyType, ValueType>::getLoadFactor() const{
    return ((double)m_elements)/m_capacity;
}

template<class KeyType, class ValueType>
inline
void MyHash<KeyType, ValueType>::reset(){
    //for everything in the map, delete the node
    for(int i = 0 ; i < m_capacity; i++){
        Node<KeyType, ValueType> * node = (m_map)[i];
        while(node != nullptr){
            Node<KeyType, ValueType> * temp = node;
            node = node->next;
            delete temp;
        }
    }
    //delete the array space
    delete [] m_map;
    //reinitialize and set everything to nullptr
    m_map = new Node<KeyType, ValueType> * [100];
    m_elements = 0;
    m_capacity = 100;
    for(int i = 0; i < m_capacity; i++){
        (m_map)[i] = nullptr;
    }
}

template<class KeyType, class ValueType>
MyHash<KeyType, ValueType>::~MyHash(){
    //destruction just deletes everything and deletes the array space
    for(int i = 0 ; i < m_capacity; i++){
        Node<KeyType, ValueType> * node = (m_map)[i];
  		while(node != nullptr){
		  
            Node<KeyType, ValueType> * temp = node;
            node = node->next;
            delete temp;
        }
    }
    delete [] m_map;
}
#endif /* MyHash_hpp */

