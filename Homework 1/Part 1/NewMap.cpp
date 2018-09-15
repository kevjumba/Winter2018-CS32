#include <iostream>
#include <cstdlib>
using namespace std;

#include "NewMap.h"


Map::Map()       // Create an empty Map (i.e., one with no key/value pairs)
{
    keys = new KeyType[DEFAULT_MAX_ITEMS];
    values = new ValueType[DEFAULT_MAX_ITEMS];
    m_size = 0;
    MAX_SIZE = DEFAULT_MAX_ITEMS;
}

Map::Map(int size){
    if(size < 0) exit(1);
    keys = new KeyType[size];
    values = new ValueType[size];
    MAX_SIZE = size;
    m_size = 0;
}

Map& Map::operator=(const Map &other)
{
    if(&other == this){
        return (*this);
    }
    delete [] keys;
    delete [] values;
    m_size = other.m_size;
    MAX_SIZE = other.MAX_SIZE;
    keys = new KeyType[MAX_SIZE];
    values = new ValueType[MAX_SIZE];
    for (int i = 0; i < m_size; i++){
        keys[i] = other.keys[i];
        values[i] = other.values[i];
    }
    return (*this);
}
                   
Map::Map(const Map &other)
{
    m_size = other.m_size;
    MAX_SIZE = other.MAX_SIZE;
    keys = new KeyType[m_size];
    values = new ValueType[m_size];
    for (int i=0; i<other.m_size; i++)
    {
        keys[i] = other.keys[i];
        values[i] = other.values[i];
    }
}

// Return true if the Map is empty, otherwise false.
bool Map::empty() const
{
    return (m_size<=0);
}

// Return the number of key/value pairs in the Map.
int Map::size() const
{
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
// If key is not equal to any key currently in the Map, and if the
// key/value pair can be added to the Map, then do so and return true.
// Otherwise, make no change to the Map and return false (indicating
// that either the key is already in the Map, or the Map has a fixed
// capacity and is full).
{
    if(m_size >= MAX_SIZE ) return false;
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
// If key is equal to a key currently in the Map, then make that key no
// longer Map to the value it currently Maps to, but instead Map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the Map and return false.
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
// If key is equal to a key currently in the Map, then make that key no
// longer Map to the value it currently Maps to, but instead Map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the Map and if the
// key/value pair can be added to the Map, then do so and return true.
// Otherwise, make no change to the Map and return false (indicating
// that the key is not already in the Map and the Map has a fixed
// capacity and is full).
{
    if(!update(key, value))
        return insert(key, value);
    return true;
}
bool Map::erase(const KeyType& key)
// If key is equal to a key currently in the Map, remove the key/value
// pair with that key from the Map and return true.  Otherwise, make
// no change to the Map and return false.
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
// Return true if key is equal to a key currently in the Map, otherwise
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
// If key is equal to a key currently in the Map, set value to the
// value in the Map that that key Maps to, and return true.  Otherwise,
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
// key and value of one of the key/value pairs in the Map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)
{
    if(i<0 || i >= size()) return false;
    key = keys[i];
    value = values[i];
    return true;
}

/*Change the implementation of the swap function so that the number of statement executions when swapping two maps is the same no matter how many key/value pairs are in the maps. (You would not satisfy this requirement if, for example, your swap function caused a loop to visit each pair in the map, since the number of statements executed by all the iterations of the loop would depend on the number of pairs in the map.)*/
void Map::swap(Map& other)
// Exchange the contents of this Map with the other one.
//----------------Check what he means--------------------
{
    Map temp;
    temp = other;
    other = *this;
    *this = temp;
}


Map::~Map(){
    delete [] keys;
    delete [] values;
}

