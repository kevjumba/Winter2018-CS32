//
//  main.cpp
//  Homework 1
//
//  Created by Kevin Zhang on 1/17/18.
//  Copyright © 2018 Kevin Zhang. All rights reserved.
//
#include "CarMap.h"
#include "Map.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test();

int main()
{
  test();
}

void test(){
  
  CarMap carMap;
  assert(carMap.fleetSize() == 0);
  assert(!carMap.useGas("abc", 0));
  assert(!carMap.addGas("abc", 222));
  assert(carMap.gas("abc") == -1);
  assert(!carMap.useGas("abc", 2));
  assert(carMap.addCar("abc"));
  assert(carMap.fleetSize() == 1);
  assert(carMap.addGas("abc", 22));
  assert(carMap.gas("abc") == 22);
  assert(carMap.useGas("abc", 22));
  assert(!carMap.useGas("abc", 1));
  assert(!carMap.addCar("abc"));
  assert(carMap.fleetSize() == 1);
  assert(carMap.addCar("cdf"));
  assert(carMap.fleetSize() == 2);
  assert(carMap.addGas("cdf", 2));
  assert(carMap.gas("cdf")==2);
  cout<<"Passed all tests"<<endl;
    
}
