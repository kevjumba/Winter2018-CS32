#include <iostream>
using namespace std;

#include "Map.h"


Map::Map()       // Create an empty map (i.e., one with no key/value pairs)
{
    m_size = 0;
}

// Return true if the map is empty, otherwise false.
bool Map::empty() const
{
    return (m_size<=0);
}

 // Return the number of key/value pairs in the map.
int Map::size() const
{
    return m_size;
}
bool Map::insert(const KeyType& key, const ValueType& value)
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full).
{
    if(m_size >= DEFAULT_MAX_ITEMS - 1) return false;
    for(int i = 0 ; i < m_size; i++){
        if(keys[i] == key){
            return false;
        }
    }
    keys[m_size] = key;
    values[m_size] = value;
    m_size++;
    return true;
}
bool Map::update(const KeyType& key, const ValueType& value)
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.
{
    for(int i = 0 ; i < m_size; i++){
        if(keys[i] == key){
            values[i] = value;
            return true;
        }
    }
    return false;
}
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // If key is not equal to any key currently in the map and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that the key is not already in the map and the map has a fixed
    // capacity and is full).
{
    if(!update(key, value))
        return insert(key, value);
    return true;
}
bool Map::erase(const KeyType& key)
    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.
{
    for(int i = 0; i < m_size; i++){
        if(keys[i] == key){
            for(int j = i; j < m_size; j++){
                keys[j] = keys[j+1];
                values[j] = values[j+1];
            }
            m_size--;
            return true;
        }
    }
    return false;
}
bool Map::contains(const KeyType& key) const
    // Return true if key is equal to a key currently in the map, otherwise
    // false.
{
    for(int i = 0; i < m_size; i++){
        if(keys[i] == key){
            return true;
        }
    }
    return false;
}
bool Map::get(const KeyType& key, ValueType& value) const
    // If key is equal to a key currently in the map, set value to the
    // value in the map that that key maps to, and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.
{
    for(int i = 0; i < m_size; i++){
        if(keys[i] == key){
            value = values[i];
            return true;
        }
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of one of the key/value pairs in the map and return
    // true.  Otherwise, leave the key and value parameters unchanged and
    // return false.  (See below for details about this function.)
{
    if(i<0 || i > size()) return false;
    key = keys[i];
    value = values[i];
    return true;
}

void Map::swap(Map& other)
    // Exchange the contents of this map with the other one.
{
    Map tempMap;
    tempMap = other;
    other = *this;
    *this = tempMap;
//    for(int i = 0 ; i < other.size(); i++){
//        KeyType key;
//        ValueType value;
//        other.get(i, key, value);
//        tempMap.insert(key, value);
//    }
//
//    for(int i = 0 ; i < other.size(); i++){
//        KeyType key;
//        ValueType value;
//        other.get(i, key, value);
//        other.erase(key);
//        i--;
//    }
//
//    for(int i = 0; i < size(); i++){
//        KeyType key;
//        ValueType value;
//        get(i, key, value);
//        other.insert(key, value);
//    }
//    for(int i = 0 ; i < size(); i++){
//        KeyType key;
//        ValueType value;
//        get(i, key, value);
//        erase(key);
//        i--;
//    }
//
//    for(int i = 0; i<tempMap.size();i++){
//        KeyType key;
//        ValueType value;
//        tempMap.get(i, key, value);
//        insert(key, value);
//    }
    
}
