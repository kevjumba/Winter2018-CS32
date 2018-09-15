//
//  CarMap.cpp
//  Homework 1
//
//  Created by Kevin Zhang on 1/17/18.
//  Copyright © 2018 Kevin Zhang. All rights reserved.
//
#include "CarMap.h"

CarMap::CarMap(){
    carMap = Map();
}

bool CarMap::addCar(std::string license)
// If a car with the given license plate is not currently in the map,
// and there is room in the map, add an entry for that car recording
// that it has 0 gallons of gas in it, and return true.  Otherwise,
// make no change to the map and return false.{
{
    return (carMap.insert(license, 0));
}

double CarMap::gas(std::string license) const{
    double gas;
    if(carMap.get(license, gas)){
        return gas;
    }
    return -1;
}
// If a car with the given license plate is in the map, return the
// number of gallons of gas in its tank; otherwise, return -1.

bool CarMap::addGas(std::string license, double gallons)
// If no car with the given license plate is in the map or if
// gallons is negative, make no change to the map and return
// false.  Otherwise, increase the number of gallons of gas in the
// indicated car by the gallons parameter and return true.
{
    if(carMap.contains(license)){
        double cur;
        carMap.get(license, cur);
        carMap.update(license, cur+gallons);
        return true;
    }
    return false;
}

bool CarMap::useGas(std::string license, double gallons)
// If no car with the given license plate is in the map or if
// gallons is negative, make no change to the map and return
// false.  Otherwise, decrease the number of gallons of gas in the
// indicated car by the gallons parameter and return true.
{
    if(carMap.contains(license)){
        double cur;
        carMap.get(license, cur);
        if(cur<gallons) return false;
        carMap.update(license, cur-gallons);
        return true;
    }
    return false;

}

int CarMap::fleetSize() const  // Return the number of cars in the CarMap.
{
    return carMap.size();
}

void CarMap::print() const
// Write to cout one line for every car in the map.  Each line
// consists of the car's license plate, followed by one space,
// followed by the number of gallons in that car's tank.  Write
// no other text.
{
    for(int i = 0; i < carMap.size(); i++){
        string license;
        double gallons;
        carMap.get(i, license, gallons);
        cout<<license<<" "<< gallons<<endl;
    }
}

