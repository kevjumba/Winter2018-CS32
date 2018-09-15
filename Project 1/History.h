//
//  History.hpp
//  Project 1
//
//  Created by Kevin Zhang on 1/10/18.
//  Copyright © 2018 Kevin Zhang. All rights reserved.
//
#include "globals.h"
#ifndef History_h
#define History_h

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    char grid[MAXROWS][MAXCOLS];
    int m_rows;
    int m_cols;
};

#endif /* History_hpp */
