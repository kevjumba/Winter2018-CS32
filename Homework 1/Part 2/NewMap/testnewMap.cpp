#include "NewMap.h"
#include <iostream>
#include <cassert>
#include <string>
using namespace std;


void test()
{
    Map m1;
    Map m2;
    m1.insert("Fred", 3);
    m1.insert("swag", 2);
    m1.insert("dragon", 5);
    m2.insert("drag", 32);
    m2.insert("butt", 32);

    m1.swap(m2);
    assert(m1.contains("drag")&& m1.contains("butt") && m1.size() == 2);
    assert(m2.contains("Fred") && m2.contains("swag") && m2.contains("dragon") && m2.size() ==3);
    Map m3 = m1;
    assert(m3.contains("drag")&&m3.contains("butt") && m3.size() == 2);
    
    m2 = m1;
    assert(m2.contains("drag")&&m2.contains("butt") && m2.size() == 2);
    cout<<"Passed All Tests"<<endl;

}

int main()
{
  test();
  Map m(0);  // maps strings to doubles
  assert(m.empty()); // should return true as map m(0) is empty
  Map m2(2);
  assert(m2.empty()); // should return true as map m(0) is empty
  ValueType t = 10.1;
  KeyType t1 = "test";
    
  ValueType t2 = 10.1;
  KeyType t3 = "test";
    
  ValueType t4 = 10.12;
  KeyType t5 = "testo";
    
  ValueType t6 = 11.12;
  KeyType t7 = "kangaroo";
    
    
  assert(m2.insert(t1, t));  //checks for insert
  assert(m2.size() == 1);
    
  assert(!m2.insert(t3, t2));// checks for repeat
  assert(m2.size() == 1);
    
  assert(m2.insert(t5, t4)); //checks for able to add
  assert(m2.size() == 2);
    
  assert(!m2.insert(t7, t6)); //checks for full capacity
  assert(m2.size() == 2);
    
  KeyType q1 = "test";
  ValueType q = 250.03;
    
  KeyType q2 = "tesla";
  ValueType q3 = 250.03;
  assert(m2.update(q1, q)); // should return true
  ValueType q4 = 0;
  m2.get(q1, q4);// checks for changed vaue
  assert(q4 == 250.03);
  assert(!m2.update(q2, q3)); // should return false
    
  KeyType w = "test";
  ValueType w1 = 250.23;
  assert(m2.insertOrUpdate(w, w1));
    
  ValueType w3 = 0;
  m2.get(w, w3);
  assert(w3 == 250.23);
    
  KeyType w4 = "toy";
  ValueType w5 = 10.00;
  assert(!m2.insertOrUpdate(w4, w5));
  m2.erase(w);
    
  assert(m2.insertOrUpdate(w4, w5));
    
  assert(m2.erase(w4));// checks erase function
  assert(m2.size() == 1);
  ValueType r = 0;
  assert(m2.get(t5, r));
  assert(r == 10.12);
  assert(m2.insertOrUpdate(w4, w5));
  assert(!m2.erase(w));
    
  //check contains function
  assert(!m2.contains(w));
  assert(m2.contains(w4));
  ///tests get function
  ValueType r2 = 0;
  assert(!m2.get(q1, r2));
  // tests get i function
  ValueType r5 = 0;
  KeyType r6 = "";
  assert(m2.get(0, r6, r5));
  assert(r5 == t4);
  assert(r6 == t5);
  assert(!m2.get(2, r6, r5));
  assert(r5 == t4);
  assert(r6 == t5);    
  cout << "Passed all tests" << endl;
}

