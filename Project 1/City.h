//
//  City.hpp
//  Project 1
//
//  Created by Kevin Zhang on 1/10/18.
//  Copyright © 2018 Kevin Zhang. All rights reserved.
//
#include "globals.h"
#include "History.h"
class Player;
class Flatulan;

#ifndef City_h
#define City_h
class City
{
public:
    // Constructor/destructor
    City(int nRows, int nCols);
    ~City();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     flatulanCount() const;
    int     nFlatulansAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;
    
    // Mutators
    bool  addFlatulan(int r, int c);
    bool  addPlayer(int r, int c);
    void  preachToFlatulansAroundPlayer();
    void  moveFlatulans();
    History& history();
    
private:
    int       m_rows;
    int       m_cols;
    Player*   m_player;
    Flatulan* m_flatulans[MAXFLATULANS];
    int       m_nFlatulans;
    History hist;
    
    // Helper functions
    bool isInBounds(int r, int c) const;
};
#endif
