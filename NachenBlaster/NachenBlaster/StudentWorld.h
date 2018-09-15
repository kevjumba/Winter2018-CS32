#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <list>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void removeDeadObjects();
    void addActor(Actor* actor);
    void dealWithCollisions(Actor * actor);
    void incrementShipDestroyed();
    Actor * getNachenBlaster();
    virtual ~StudentWorld();
private:
    list<Actor *> actors;
    Actor * nachenBlaster;
    int m_alienShipsDestroyed;
    int m_shipsOnScreen;
};

#endif // STUDENTWORLD_H_
