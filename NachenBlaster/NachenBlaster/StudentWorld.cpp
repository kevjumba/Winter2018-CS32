 #include "StudentWorld.h"
#include <stdlib.h>
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}


StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{}


int StudentWorld::init()
{
    //initializes all objects in the current level
    m_alienShipsDestroyed = 0;
    m_shipsOnScreen = 0;
    nachenBlaster = new NachenBlaster(this);
    Actor * star;
    //generate 30 new stars
    for(int i = 0; i < 30; i++){
        int randX = randInt(0, VIEW_WIDTH-1);
        int randY = randInt(0, VIEW_HEIGHT-1);
        double randD = randInt(500, 5000)/10000.00;
        star = new Star(this, randX, randY, randD);
        actors.push_back(star);
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
//==============Determine if program should spawn star ===============================
    int spawnStar = rand() % 15;
    if(spawnStar == 0){
        Actor * star;
        int randY = randInt(0, VIEW_HEIGHT-1);
        double randD = randInt(500, 5000)/10000.00;
        star = new Star(this, VIEW_WIDTH-1, randY, randD);
        actors.push_back(star);
    }
//==============Determine if program should spawn aliens ===============================
    //remaing ships needed to destroy to complete level
    
    int remainingShips = 6+(4*this->getLevel()) - m_alienShipsDestroyed;
    //maxships on screen
    int maxShips = 4 + (0.5*this->getLevel());
    if(m_shipsOnScreen < min(maxShips, remainingShips)){
        int S1 = 60;
        int S2 = 20 + this->getLevel()*5;
        int S3 = 5 + this->getLevel()*10;
        double S = S1 + S2 + S3;
        double spawnSmallgon = S1/S;
        double spawnSmoregon = S2/S;
        double randNum = randInt(0, 10000)/10000.0;
        //if probability dictates spawn a smallgon
        if(randNum <= spawnSmallgon){
            Actor * smallgon;
            smallgon = new Smallgon(this, this->getLevel());
            this->actors.push_back(smallgon);
            m_shipsOnScreen++;
        }
        //if probability dictates spawn a smoregon
        else if(randNum>spawnSmallgon && randNum <= (spawnSmallgon+spawnSmoregon)){
            Actor * smoregon;
            smoregon = new Smoregon(this, this->getLevel());
            this->actors.push_back(smoregon);
            m_shipsOnScreen++;
        }
        //if probability dictates spawn a snagglegon
        else {
            Actor * snagglegon;
            snagglegon = new Snagglegon(this, this->getLevel());
            this->actors.push_back(snagglegon);
            m_shipsOnScreen++;
        }
    }
    //remove the dead objects in the studentWorld
    removeDeadObjects();
    //first have the nachenblaster doSomething
    nachenBlaster->doSomething();
    //then have everything in the list of actors doSomething
    list<Actor *>::iterator it;
    it = actors.begin();
    while(it!=actors.end()){
        (*it)->doSomething();
        it++;
        //if the nachenBlaster has died
        if(!nachenBlaster->getState()){
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        //if the number of alien ships destroyed is the number required to pass the level
        if(m_alienShipsDestroyed == (6+(4*this->getLevel()))){
            this->playSound(SOUND_FINISHED_LEVEL);
            return GWSTATUS_FINISHED_LEVEL;
        }
    }
    removeDeadObjects();
    //remove the dead objects again
    
    //get the percentage health, percentage cabbages and torpedoes left
    int percentageHealth = ((((NachenBlaster * )(this->getNachenBlaster()))->getHealth())/50.0)*100;
    int percentageCabbages = ((NachenBlaster * )(this->getNachenBlaster()))->getCabbages()*10/3;
    int torpedoes =((NachenBlaster * )(this->getNachenBlaster()))->getTorpedoes();

    //add to the game text in the way the spec details
    string str = "Lives: "+to_string(this->getLives())+"  Health: "+to_string(percentageHealth)+"%  Score: "+to_string(this->getScore())+"  Level: "+to_string(this->getLevel())
                +"  Cabbages: "+to_string(percentageCabbages)+"%  Torpedoes: "+to_string(torpedoes);
    this->setGameStatText(str);
    return GWSTATUS_CONTINUE_GAME;
}

double euclidian_dist(int x1, int y1, int x2, int y2){
    //returns the distance between (x1, y1) and (x2, y2)
    return (sqrt(pow(x1-x2, 2)+ pow(y1-y2, 2)));
}

void StudentWorld::dealWithCollisions(Actor * actor){
    //iterates through the list of actors
    list<Actor *>::iterator it;
    it = actors.begin();
    while(it!=actors.end()){
        int x1 = actor->getX();
        int x2 = (*it)->getX();
        int y1 = actor->getY();
        int y2 = (*it)->getY();
        double r1 = actor->getRadius();
        double r2 = (*it)->getRadius();
        bool isSameName = (actor->getName()==(*it)->getName());
        //if the actors are not the same and the euclidian dist is less than what is specified in the spec
        if(!isSameName && euclidian_dist(x1, y1, x2, y2)< (0.75*(r1+r2))){
            //call sufferCollision on both sufferees and each will deal with half of the collision
            (*it)->sufferCollision(actor);
            actor->sufferCollision((*it));
        }
        it++;
    }
    //check to see if the nachenblaster has collided with the actor and do the same thing
    int x1 = actor->getX();
    int x2 = (nachenBlaster)->getX();
    int y1 = actor->getY();
    int y2 = (nachenBlaster)->getY();
    double r1 = actor->getRadius();
    double r2 = (nachenBlaster)->getRadius();
    bool isSameName = (actor->getName()==nachenBlaster->getName());
    if(!isSameName && euclidian_dist(x1, y1, x2, y2)< (0.75*(r1+r2))){
        nachenBlaster->sufferCollision(actor);
        actor->sufferCollision(nachenBlaster);
    }
}

void StudentWorld::addActor(Actor *actor){
    //add an actor to the list
    actors.push_back(actor);
}

void StudentWorld::cleanUp()
{
    //when the nachenblaster completes level or loses a life => responsible for freeing all actors that are currently in the game
    //if the nachenblaster hasnt already been freed
    if(nachenBlaster!=nullptr){
        delete nachenBlaster;
        nachenBlaster = nullptr;
    }
    list<Actor *>::iterator it;
    it = actors.begin();
    while(it!=actors.end()){
        //delete the current element and erase it
        delete (*it);
        it = actors.erase(it);
    }
}

void StudentWorld::removeDeadObjects(){
    list<Actor *>::iterator it;
    it = actors.begin();
    while(it!=actors.end()){
        if((*it)->isDead()){
            //if the actor is dead
            //if the actor is dead and is an alien, decrement ships on screen
            if((*it)->getName() == IID_SMALLGON || (*it)->getName() == IID_SNAGGLEGON || (*it)->getName() == IID_SMOREGON){
                m_shipsOnScreen--;
            }
            //delete the actor and erase it
            delete (*it);
            it = actors.erase(it);
        }
        else{
            it++;
        }
    }
}


void StudentWorld::incrementShipDestroyed(){
    //increment the alien ships destroyed
    m_alienShipsDestroyed++;
}

Actor * StudentWorld::getNachenBlaster(){
    return nachenBlaster;
}

StudentWorld::~StudentWorld(){
    cleanUp();
}
