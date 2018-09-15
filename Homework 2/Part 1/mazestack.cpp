#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    stack<Coord> path;
    path.push(Coord(sr, sc));
    maze[sr][sc] = '#';
    while(!path.empty())
    {
        Coord temp = path.top();
        path.pop();
        int r = temp.r();
        int c = temp.c();
        if(r == er && c == ec){
            return true;
        }
        
        if(maze[r][c+1]!='#' && maze[r][c+1]!='X'){
            maze[r][c+1]='#';
            path.push(Coord(r, c+1));
        }

        if(maze[r+1][c]!='#' && maze[r+1][c]!='X'){
            maze[r+1][c]='#';
            path.push(Coord(r+1, c));
        }
        if(maze[r][c-1]!='#' && maze[r][c-1]!='X'){
            maze[r][c-1]='#';
            path.push(Coord(r, c-1));
        }
        if(maze[r-1][c]!='#' && maze[r-1][c]!='X'){
            maze[r-1][c]='#';
            path.push(Coord(r-1, c));
        }
    }
    return false;
}


