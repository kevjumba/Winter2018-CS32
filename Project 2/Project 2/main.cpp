#include "Map.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Map m;
    ValueType valueTemp;
    KeyType keyTemp;
    assert(m.empty());  //check if m is initialized to empty
    assert(m.size() == 0); //check if m has size 0
    assert(!m.erase("1")); //try erasing
    assert(!m.contains("1"));
    assert(m.insert("a", 1)); //insert with nothing inside
    assert(m.contains("a")); //see if m contains a just inserted and check contains
    assert(m.get("a", valueTemp)); //see if you actually can get 'a'
    assert(valueTemp == 1); //check if get actually worked
    assert(m.get(0, keyTemp, valueTemp)); //check get index
    assert(keyTemp == "a"); //check if get index actually worked
    assert(valueTemp == 1); //check if valueTemp was stored correctly
    assert(m.erase("a")); //check if we can erase
    assert(m.size()==0 && !m.contains("a")); //check if the erase actually erased it
    assert(m.insert("a", 1)); //insert a again
    assert(!m.insert("a", 1.2)); //try inserting the same a
    assert(m.insert("b", 2)); //check if i can insert such that there is a head and tail
    assert(m.insert("c", 3)); //now insert one such that there is one in the middle
    assert(m.contains("b") && m.contains("c")); //check if they were inserted correctly
    assert(m.insertOrUpdate("a", 2.3)); //check if we can insert
    assert(m.insertOrUpdate("d", 3.4)); //check if insertions don't return false if it doesn't exist
    assert(m.get("a", valueTemp));
    assert(valueTemp==2.3);
    assert(m.get("d", valueTemp));
    assert(valueTemp==3.4);
    Map m2;
    m2 = m;
    assert(m2.size() == 4 && m2.contains("a") && m2.contains("b") && m2.contains("c") && m2.contains("d")); //assert if everything copied over correctly using assignment operator
    Map m3 = m;
    assert(m3.size() == 4 && m3.contains("a") && m3.contains("b") && m3.contains("c") && m3.contains("d")); //assert if everything copied over when copy constructor using assignment
    Map m4(m);
    assert(m4.size() == 4 && m4.contains("a") && m4.contains("b") && m4.contains("c") && m4.contains("d")); //assert if everything copied over when copy constructor using default
    
    Map m5;
    assert(m5.insert("1", 5));
    assert(m5.insert("2", 6.2));
    assert(m5.insert("3", 2.7));
    assert(m5.insert("4", 3.2));
    assert(m5.insert("5", 3.1));
    m5.swap(m); //check swap
    assert(m5.size() == 4 && m5.contains("a") && m5.contains("b") && m5.contains("c") && m5.contains("d")); //check if swap worked
    
    assert(m5.get("a", valueTemp)); //check if values in the swap are right
    assert(valueTemp == 2.3);
    assert(m5.get("b", valueTemp));
    assert(valueTemp == 2);
    assert(m.size() == 5 && m.contains("1") && m.contains("2") && m.contains("3") && m.contains("4") && m.contains("5")); //check if swap worked
    assert(m.get("1", valueTemp)); //check if values in the swap are right
    assert(valueTemp == 5);
    assert(m.get("2", valueTemp));
    assert(valueTemp == 6.2);
    
    Map map;
    Map map1;
    Map map2;
    assert(combine(map, map1, map2));
    assert(map.size()==0 && map1.size() ==0 && map2.size() ==0);
    map.swap(map1);
    assert(map.size()==0 && map1.size() ==0);
    
    assert(map.insert("a", 1));
    assert(map.insert("b", 2));
    assert(map.insert("c", 3));
    assert(map.insert("d", 4));
    assert(map.insert("e", 5));
    
    assert(map1.insert("a", 1));
    
    subtract(map, map1, map2);  //test subtract
    
    assert(map2.contains("b"));  //check if the subtract command actually worked
    assert(map2.contains("c"));
    assert(map2.contains("d"));
    assert(!map2.contains("a"));
    assert(map2.get("b", valueTemp));
    assert(valueTemp == 2);
    assert(map1.update("a", 2)); //change a so that they are different in map1 and map
    assert(map1.insert("b", 2)); //insert b so there is one that is the same in map1 and map
    assert(map1.insert("f", 4));
    assert(!combine(map, map1, map2)); //check if combine returns false
    assert(!map2.contains("a")); //check if map doesn't contain a since there was 2 instances with different values
    assert(map2.contains("b"));  //check if other normal cases of insert are contained
    assert(map2.contains("c"));
    assert(map2.contains("d"));
    //assert(map2.contains("e"));
    assert(map2.contains("f"));  //check if a key that's in m2 but not in m1 in inserted
    assert(map2.get("f", valueTemp));
    assert(valueTemp == 4); //check the value of this key
    
    Map g;
    g.insert("a", 1);
    assert(g.insertOrUpdate("a", 2.3));
    assert(g.insertOrUpdate("b", 2.3));
    assert(!g.insert("a", 2.3));
    assert(!g.insert("a", 1));
    KeyType key;
    ValueType value;
    assert(g.get(0, key, value));
    assert(key == "a" && value ==2.3);
    
    assert(g.get(1, key, value));
    assert(key == "b" && value == 2.3);
    assert(!g.get(2, key, value));
    cout << "Passed all tests" << endl;
}
