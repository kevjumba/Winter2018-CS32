//
//  main.cpp
//  Hwk3_P3
//
//  Created by Kevin Zhang on 2/11/18.
//  Copyright © 2018 Kevin Zhang. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
/*
 If the start location is equal to the ending location, then we've
 solved the maze, so return true.
 Mark the start location as visited.
 For each of the four directions,
 If the location one step in that direction (from the start
 location) is unvisited,
 then call pathExists starting from that location (and
 ending at the same ending location as in the
 current call).
 If that returned true,
 then return true.
 */
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    if(sr == er && sc == ec){
        return true;
    }
    maze[sr][sc] = '#';
    
    if(maze[sr][sc+1]!='#' && maze[sr][sc+1]!='X'){
        if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec)) return true;
    }
    
    if(maze[sr+1][sc]!='#' && maze[sr+1][sc]!='X'){
        if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec)) return true;
    }
    if(maze[sr][sc-1]!='#' && maze[sr][sc-1]!='X'){
        if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec)) return true;

    }
    if(maze[sr-1][sc]!='#' && maze[sr-1][sc]!='X'){
        if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec)) return true;
    }
    return false;
}
