#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>
using namespace std;


//==========================Actor Functions=========================================

Actor::Actor(StudentWorld * world, int imageID, int x, int y, int direction, double size, int depth) :
GraphObject(imageID, x, y, direction, size, depth){
    //initialize the graphObject, and all the corresponding private members including pointer to student world
    studentWorld = world;
    m_state = 1;
    name = imageID;
}

int Actor::getName(){
    //return the image ID or name of the actor
    return name;
}

StudentWorld * Actor::getWorld(){
    //returns the world
    return studentWorld;
}

void Actor::setState(int state){
    //sets the actor's state
    m_state = state;
}

int Actor::getState(){
    //get the actor's state
    return m_state;
}

bool Actor::isDead(){
    //returns true if the actor is dead, false otherwise
    return (m_state==0);
}

//==========================NachenBlaster Functions ====================================

NachenBlaster::NachenBlaster(StudentWorld * world):
Actor(world, IID_NACHENBLASTER, 0, 128, 0, 1.0, 0){
    //initializes private members of Nachenblaster and calls the constructor on actor
    m_hitpoints = 50;
    m_cabbage_energy = 30;
    m_torpedoCount = 0;
}

void NachenBlaster::doSomething(){
    //check if hitpoints are 0, if they are set the nachenblaster to dead
    if(m_hitpoints<=0){
        this->setState(0);
        return;
    }
    //give nachenblaster a cabbage energy point if his energy is less than 30
    if(this->m_cabbage_energy<30){
        m_cabbage_energy++;
    }
    int key;
    //grabs a key and performs action based on what that key is
    if(getWorld()->getKey(key)){
        switch(key){
            case KEY_PRESS_UP:
                if(getY()+6<VIEW_HEIGHT){
                    //move up 6 pixels
                    this->moveTo(getX(), getY()+6);
                } break;
            case KEY_PRESS_LEFT:
                if(getX()-6>=0){
                    //move left 6 pixels
                    this->moveTo(getX()-6, getY());
                } break;
            case KEY_PRESS_RIGHT:
                //move right 6 pixels
                if(getX()+6<VIEW_WIDTH){
                    this->moveTo(getX()+6, getY());
                } break;
            case KEY_PRESS_DOWN:
                if(getY()-6>=0){
                    //move down 6 pixels
                    this->moveTo(getX(), getY()-6);
                } break;
            case KEY_PRESS_SPACE:
                //if the player has more than or equal to 5 cabbage energy, fire cabbage
                if(this->m_cabbage_energy>=5){
                    this->fireCabbage();
                }
                break;
            case KEY_PRESS_TAB:
                //fire torpedo
                this->fireTorpedo();
                break;
        }
    }
    
}

void NachenBlaster::fireTorpedo(){
    //if there are more than 0 torpedoes
    if(m_torpedoCount>0){
        //construct one 12 units to the right of the nachenblaster with direction 0(to the left)
        //add the actor to the studentWorld and play torpedo sound, then decrement numTorpedoes
        Actor * torpedo;
        torpedo = new F_Torpedo(getWorld(), this->getX() + 12, this->getY(), 0);
        this->getWorld()->addActor(torpedo);
        this->getWorld()->playSound(SOUND_TORPEDO);
        m_torpedoCount--;
    }
    return;
}

void NachenBlaster::fireCabbage(){
    //create a new cabbage 12 units to the right of nachenblaster, add it to the studentWorld
    //play player_shoot sound
    Actor * cabbage;
    cabbage = new Cabbage(getWorld(), this->getX() + 12, this->getY());
    this->getWorld()->addActor(cabbage);
    this->getWorld()->playSound(SOUND_PLAYER_SHOOT);
    m_cabbage_energy-=5;
}


void NachenBlaster::sufferCollision(Actor * object){
    //if the object is already dead just return
    bool collided = true;
    //if the object is a smallgon or smoregon, decrease health by 5
    if(object->getName() == IID_SMALLGON || object->getName() == IID_SMOREGON){
        this->m_hitpoints-=5;
    }
    //if the object is a snagglegon decrease health by 15
    else if(object->getName()==IID_SNAGGLEGON){
        this->m_hitpoints-=15;
    }
    //if the object is a turnip, decrease health by 2 and play blast sound
    else if(object->getName()==IID_TURNIP){
        this->m_hitpoints-=2;
        this->getWorld()->playSound(SOUND_BLAST);
        object->setState(0);
    }
    //if the object is a torpedo with direction 180(to the left) decrease health by 8 and play blast
    else if(object->getName() == IID_TORPEDO && (object)->getDirection() == 180){
        this->m_hitpoints-=8;
        this->getWorld()->playSound(SOUND_BLAST);
        object->setState(0);
    }
    //if the object is a life goodie, increase player's lives
    else if(object->getName() == IID_LIFE_GOODIE){
        this->getWorld()->incLives();
    }
    //if there is repair goodie, increase hitpoints by 10
    else if(object->getName() == IID_REPAIR_GOODIE){
        this->m_hitpoints+=10;
        if(this->m_hitpoints>50){
            this->m_hitpoints=50;
        }
    }
    //if it is a torpedo goodie, give the nachenblaster 5 torpedoes
    else if(object->getName() == IID_TORPEDO_GOODIE){
        this->m_torpedoCount+=5;
    }
    //otherwise it hasnt collided with anything
    else{
        collided = false;
    }
    //if these actions make the nachenblaster's health go below 0 set it to dead.
    if(m_hitpoints<=0){
        this->setState(0);
    }
    
    return;
}

int NachenBlaster::getHealth(){
    //returns hitpoints
    return m_hitpoints;
}

int NachenBlaster::getCabbages(){
    //returns cabbage energy
    return m_cabbage_energy;
}

int NachenBlaster::getTorpedoes(){
    //returns number of torpedoes left
    return m_torpedoCount;
}

NachenBlaster::~NachenBlaster(){}

//======================Star Functions=================================================

void Star::doSomething(){
    //check if it is dead
    if(this->isDead()){
        return;
    }
    //if it has flown off the screen set it to dead
    if(this->getX()<=-1){
        this->setState(0); //DEAD
    }
    //else, we can move it 1 pixel to the left
    else{
        this->moveTo(this->getX()-1, this->getY());
    }
}

Star::~Star() {};

//==============================Projectile Functions =============================================

Projectile::Projectile(StudentWorld * world, int image_ID, int x, int y, int direction, int speed) :
Actor(world, image_ID, x, y, direction, 0.5, 1) {
    //construct projectile with a speed
    m_speed = speed;
}

void Projectile::doSomething(){
    //if the projectile is dead return
    if(this->isDead()){
        return;
    }
    //if the projectile has flown off the screen set it to dead
    if(this->getX()<0 || this->getX()>=VIEW_WIDTH){
        this->setState(0);
        return;
    }
    //check for collisions by calling studentworld function and check if collision results in death
    this->getWorld()->dealWithCollisions(this);
    if(this->isDead()){
        return;
    }
    //move it in the direction of m_speed if it is not dead
    this->moveTo(this->getX()+m_speed, this->getY());
    //if it is not a torpedo, reset the direction to 20 degrees counterclockwise
    if(this->getName()!=IID_TORPEDO){
        this->setDirection(this->getDirection()+20);
    }
    //check for collisions again
    this->getWorld()->dealWithCollisions(this);
    if(this->isDead()){
        return;
    }
}

//======================Alien Functions===============================================

Alien::Alien(StudentWorld * world, int imageID, int flightDirection, double size, int depth, int hitpoints, int flightPlanLen, double travelSpeed) :
Actor(world, imageID, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT-1), 0, size , depth){
    //initialize x to VIEW_WIDTH - 1 and y to a random number between 0 and VIEW_HEIGHT-1
    //then initalize all private members of alien
    m_hitpoints = hitpoints;
    m_flightPlanLen = flightPlanLen;
    m_travelSpeed = travelSpeed;
    m_flightDirection = flightDirection; // 1 is NW, 0 is W, -1 is SW
}

void Alien::fireProjectile(int name){
    //if the fired projectile is a turnip
    if(name == IID_TURNIP){
        //construct and allocate new turnip 14 pixels to the left of the alien
        //then play sound shoot
        //add the actor to studentWorld
        Actor * turnip;
        turnip = new Turnip(getWorld(), this->getX() - 14, this->getY());
        this->getWorld()->addActor(turnip);
        this->getWorld()->playSound(SOUND_ALIEN_SHOOT);
    }
    else if(name == IID_TORPEDO){
        //if the fired projectile is a torpedo, construct and allocate it 14 pixels to
        //the left of the alien with direction 180(left)
        //play the torpedo sound
        //add the actor to studentWorld
        this->getWorld()->playSound(SOUND_TORPEDO);
        Actor * torpedo;
        torpedo = new F_Torpedo(getWorld(), this->getX() - 14, this->getY(), 180);
        this->getWorld()->addActor(torpedo);
    }
}


void Alien::setFlightDir(int direction){
    //return the flightdirection
    m_flightDirection = direction;
}

int Alien::getFlightDir(){
    //get flightdirection
    return m_flightDirection;
}

int Alien::getFlightPlanLength(){
    //get the flight plan length
    return m_flightPlanLen;
}

void Alien::setFlightSpeed(double flightSpeed){
    //set the flight speed
    m_travelSpeed = flightSpeed;
}

double Alien::getFlightSpeed(){
    //get the travel speed
    return m_travelSpeed;
}

void Alien::setFlightPlanLength(int flightPlanLen){
    // set the flight plan length
    m_flightPlanLen = flightPlanLen;
}

int Alien::getHitpoints(){
    //return hitpoints
    return m_hitpoints;
}

void Alien::setHitpoints(int hitPoints){
    //set the aliens hitpoints
    m_hitpoints = hitPoints;
}

//======================Smallgon Functions=================================================

void Smallgon::doSomething(){
    //if the smallgon is dead return
    if(this->isDead()){
        return;
    }
    //if it has flown off screen or has died
    else if(this->getHitpoints()<=0 || this->getX() < 0){
        this->setState(0);
    }
    //deal with the collisions
    this->getWorld()->dealWithCollisions(this);
    //check if it is dead after collisions
    if(this->isDead()){
        return;
    }
    
    //if the flightplan has reached its end or the smallgon has flown off the screen to the top or bottom
    if(this->getFlightPlanLength() <= 0 || this->getY() >= VIEW_HEIGHT-1 || this->getY()<=0 ){
        //if smallgon flown off the screen, reverse direction
        if(this->getY() >= VIEW_HEIGHT -1){
            this->setFlightDir(-1);
        }
        else if(this->getY()<=0){
            this->setFlightDir(1);
        }
        //if the flightplan is 0, generate a completely new flight plan
        else if(this->getFlightPlanLength() <= 0){
            int randDirection = randInt(-1, 1);
            this->setFlightDir(randDirection);
        }
        //set a new flightplan between 1 and 32 pixels
        int newFlightLen = randInt(1, 32);
        this->setFlightPlanLength(newFlightLen);
    }
    
    if(abs(this->getWorld()->getNachenBlaster()->getY()-this->getY())<4 && (this->getWorld()->getNachenBlaster()->getX()<this->getX())){
        //if the nachenblaster is to the left of the current alien and the nachenblaster is within 4 units of the y coordinate of the smallgon
        double randNum = randInt(1, 10000)/10000.00;
        double probability = (1.0/((20.0/this->getWorld()->getLevel())+5));
        //if the randNum is within the probability range, fire a turnip
        if(randNum<=probability){
            fireProjectile(IID_TURNIP);
            return;
            //do nothing else during the current tick
        }
    }
    //based on the direction, move in a particular direction
    switch(this->getFlightDir()){
        case -1: //SW
            this->moveTo(this->getX()-this->getFlightSpeed(), this->getY()-this->getFlightSpeed());
            break;
        case 1: //NW
            this->moveTo(this->getX()-this->getFlightSpeed(), this->getY()+this->getFlightSpeed());
            break;
        case 0: //W
            this->moveTo(this->getX()-this->getFlightSpeed(), this->getY());
            break;
    }
    this->setFlightPlanLength(this->getFlightPlanLength()-1);
    //check again for collisions
    this->getWorld()->dealWithCollisions(this);
    //check if it is dead after collisions
    if(this->isDead()){
        return;
    }
    
}

void Smallgon::sufferCollision(Actor * object){
    //if the smallgon is dead return;
    if(object->isDead()) return;
    bool collided = true;
    //if collided with cabbage, decrease hitpoints by 2
    if(object->getName() == IID_CABBAGE){
        this->setHitpoints(this->getHitpoints()-2);
        object->setState(0);
    }
    //if the object is nachenblaster decrease hitpoints by 100
    else if(object->getName() == IID_NACHENBLASTER){
        this->setHitpoints(this->getHitpoints()-100);
    }
    //if object is torpedo and it is going to the left decrease hitpoints by 8
    else if(object->getName() == IID_TORPEDO && (object)->getDirection() == 0){
        this->setHitpoints(this->getHitpoints()-8);
        object->setState(0);
    }
    else{
        collided = false;
    }
    //if it did collide with something and the hitpoints is less than 0
    if(this->getHitpoints()<=0 && collided){
        //set hitpoints to 0, set it to dead, increase player score by 250, play deathsound
        //increment ships destroyed and create a new explosion object at the smallgon's location
        this->setHitpoints(0);
        this->setState(0);
        this->getWorld()->increaseScore(250);
        this->getWorld()->playSound(SOUND_DEATH);
        this->getWorld()->incrementShipDestroyed();
        Actor * explosion;
        explosion = new Explosion(this->getWorld(), this->getX(), this->getY());
        this->getWorld()->addActor(explosion);
    }
    else if(collided){
        //else just play the blast sound
        this->getWorld()->playSound(SOUND_BLAST);
    }
}


Smallgon::~Smallgon(){}


//======================Smoregon Functions=================================================

void Smoregon::doSomething(){
    //if smoregon is dead return
    if(this->isDead()){
        return;
    }
    //if hitpoints is less than or equal to 0 or it has flown off the map, set it to dead
    else if(this->getHitpoints()<=0 || this->getX() < 0){
        this->setState(0);
    }
    
    //deal with collisions
    this->getWorld()->dealWithCollisions(this);
    
    if(this->isDead()){
        return;
    }
    
    //if the flight plan has finished or the smoregon is flying off the map
    if(this->getFlightPlanLength() <= 0 || this->getY() >= VIEW_HEIGHT-1 || this->getY()<=0 ){
        //reverse the direction if it is flying off the map
        if(this->getY() >= VIEW_HEIGHT -1){
            this->setFlightDir(-1);
        }
        else if(this->getY()<=0){
            this->setFlightDir(1);
        }
        //if flight plan is 0, generate random direction
        else if(this->getFlightPlanLength() <= 0){
            int randDirection = randInt(-1, 1);
            this->setFlightDir(randDirection);
        }
        //generate new flight plan
        int newFlightLen = randInt(1, 32);
        this->setFlightPlanLength(newFlightLen);
    }
    //if nachenblaster is to the left and within 4 pixels up and down
    if(abs(this->getWorld()->getNachenBlaster()->getY()-this->getY())<4 && this->getWorld()->getNachenBlaster()->getX()<this->getX() ){
        double randNum = randInt(1, 10000)/10000.00;
        double probability = (1.0/((20.0/this->getWorld()->getLevel())+5));
        //if within probability range, fire a turnip
        if(randNum<probability){
            fireProjectile(IID_TURNIP);
            return;
            //do nothing else during the current tick
        }
        //else if in another probability range
        else if(randNum>=probability && randNum < 2* probability){
            //set the mode to ram by setting the flight direction to due west, flying straight for the edge
            //and setting the flight speed to 5
            this->setFlightDir(0);
            this->setFlightPlanLength(VIEW_WIDTH);
            this->setFlightSpeed(5);
        }
    }
    //check flight direction and move smoregon in that direction
    switch(this->getFlightDir()){
        case -1: //SW
            this->moveTo(this->getX()-this->getFlightSpeed(), this->getY()-this->getFlightSpeed());
            break;
        case 1: //NW
            this->moveTo(this->getX()-this->getFlightSpeed(), this->getY()+this->getFlightSpeed());
            break;
        case 0: //W
            this->moveTo(this->getX()-this->getFlightSpeed(), this->getY());
            break;
    }
    //decrease flightplan by 1
    this->setFlightPlanLength(this->getFlightPlanLength()-1);
    
    //deal with collisions again
    this->getWorld()->dealWithCollisions(this);
    
    if(this->isDead()){
        return;
    }
}

void Smoregon::sufferCollision(Actor * object){
    //if object is dead return
    if(object->isDead()) return;
    if(this->isDead()) return;
    bool collided = true;
    //if collided with cabbage, decrease health by 2
    if(object->getName() == IID_CABBAGE){
        object->setState(0);
        this->setHitpoints(this->getHitpoints()-2);
    }
    //if collided with nachenblaster decrease health by 100
    else if(object->getName() == IID_NACHENBLASTER){
        this->setHitpoints(this->getHitpoints()-100);

    }
    //if collided with torpedo that is going to the right decrease health by 8
    else if(object->getName() == IID_TORPEDO && (object)->getDirection() == 0){
        this->setHitpoints(this->getHitpoints()-8);
        object->setState(0);
    }
    else{
        collided = false;
    }
    //if the hitpoints is less than or equal to 0 and it did collide
    if(this->getHitpoints()<=0 && collided){
        //proceed with death animations and processes
        this->setHitpoints(0);
        this->setState(0);
        this->getWorld()->increaseScore(250);
        this->getWorld()->playSound(SOUND_DEATH);
        this->getWorld()->incrementShipDestroyed();
        int randNum = randInt(1, 3);
        if(randNum==1){
            //1/3 probability that the smoregon will drop a goodie
            randNum = randInt(1, 2);
            if(randNum == 1){
                //half chance to construct new torpedo goodie
                Actor * f_torpedo;
                f_torpedo = new T_Goodie(getWorld(), this->getX(), this->getY());
                this->getWorld()->addActor(f_torpedo);
                //add flatulence torpedo
            }
            else{
                //half change to construct new repair goodie
                Actor * repair_goodie;
                repair_goodie = new R_Goodie(getWorld(), this->getX(), this->getY());
                this->getWorld()->addActor(repair_goodie);
                //add repair goodie
            }
        }
        //finally create new explosion object
        Actor * explosion;
        explosion = new Explosion(this->getWorld(), this->getX(), this->getY());
        this->getWorld()->addActor(explosion);
    }
    else if(collided){
        //if only collided, play the blast sound
        this->getWorld()->playSound(SOUND_BLAST);
    }
}

Smoregon::~Smoregon(){}


//======================Snagglegon Functions=================================================

void Snagglegon::doSomething(){
    //if the snagglegon is dead return
    if(this->isDead()){
        return;
    }
    //if the hitpoints is less than or equal to 0 or it has flown off the left side, set it to dead
    else if(this->getHitpoints()<=0 || this->getX() < 0){
        this->setState(0);
    }
    //deal with collisions
    this->getWorld()->dealWithCollisions(this);
    
    if(this->isDead()){
        return;
    }
    //if the snagglegon is flying off the map
    if(this->getY() >= VIEW_HEIGHT-1 || this->getY() <= 0 ){
        //reverse direction
        if(this->getY() >= VIEW_HEIGHT -1){
            this->setFlightDir(-1);
        }
        else if(this->getY()<=0){
            this->setFlightDir(1);
        }
    }
    //if the nachenblaster is within 4 pixels y coordinate and to the left of the snagglegon
    if(abs(this->getWorld()->getNachenBlaster()->getY()-this->getY())<4 && this->getWorld()->getNachenBlaster()->getX()<this->getX() ){
        //there is the below probability change it will fire a torpedo
        double randNum = randInt(1, 10000)/10000.00;
        double probability = (1.0/((15.0/this->getWorld()->getLevel())+10));
        if(randNum<probability){
            fireProjectile(IID_TORPEDO);
            return;
            //do nothing else during current tick
        }
    }
    //based on flight direction move in a particular direction
    switch(this->getFlightDir()){
        case -1: //SW
            this->moveTo(this->getX()-this->getFlightSpeed(), this->getY()-this->getFlightSpeed());
            break;
        case 1: //NW
            this->moveTo(this->getX()-this->getFlightSpeed(), this->getY()+this->getFlightSpeed());
            break;
        case 0: //W
            this->moveTo(this->getX()-this->getFlightSpeed(), this->getY());
            break;
    }

    //check again for collisions
    this->getWorld()->dealWithCollisions(this);
    //check if it is dead after collisions
    if(this->isDead()){
        return;
    }
}

void Snagglegon::sufferCollision(Actor * object){
    //if the object is already dead return
    if(object->isDead()) return;
    if(this->isDead()){
        return;
    }
    bool collided = true;
    //if the snagglegon hit a cabbage, decrease hitpoints by 2
    if(object->getName() == IID_CABBAGE){
        this->setHitpoints(this->getHitpoints()-2);
        object->setState(0);
    }
    //if snagglegon hit a nachenblaster decrease hitpoints by 100
    else if(object->getName() == IID_NACHENBLASTER){
        this->setHitpoints(this->getHitpoints()-100);
    }
    //if the object is a torpedo and the torpedo's direction is to the right, decrease hitpoints by 8
    else if(object->getName() == IID_TORPEDO && (object)->getDirection() == 0){
        this->setHitpoints(this->getHitpoints()-8);
        object->setState(0);
    }
    else{
        collided = false;
    }
    //if the snagglegon died from the collision
    if(this->getHitpoints()<=0 && collided){
        //increase points by 1000
        this->setHitpoints(0);
        this->setState(0);
        this->getWorld()->increaseScore(1000);
        this->getWorld()->playSound(SOUND_DEATH);
        this->getWorld()->incrementShipDestroyed();
        int randNum = randInt(1, 6);
        //there is 1/6 chance a life_goodie will spawn
        if(randNum==1){
            Actor * life_goodie;
            life_goodie = new E_Goodie(this->getWorld(), this->getX(), this->getY());
            this->getWorld()->addActor(life_goodie);
            //add an extra life goodie
        }
        Actor * explosion;
        explosion = new Explosion(this->getWorld(), this->getX(), this->getY());
        this->getWorld()->addActor(explosion);
    }
    else if(collided){
        //if only collided, play blast
        this->getWorld()->playSound(SOUND_BLAST);
    }
}

Snagglegon::~Snagglegon(){}

//============================== Goodie Functions ============================================

void Goodie::sufferCollision(Actor * object){
    if(object->getName() == IID_NACHENBLASTER){
        //increase the nachenblaster score by 100
        //set goodie to dead and play sound goodie
        this->getWorld()->increaseScore(100);
        this->setState(0);
        this->getWorld()->playSound(SOUND_GOODIE);
    }
}

void Goodie::doSomething(){
    //if goodie is dead return
    if(this->isDead()){
        return;
    }
    //deal with collisions
    this->getWorld()->dealWithCollisions(this);
    if(this->isDead()){
        return;
    }
    //move down and to the left by 0.75
    this->moveTo(this->getX()-0.75, this->getY()-0.75);
    //if the goodie has flown off the screen set it to dead
    if(this->getX()<=0 || this->getY() <= 0){
        this->setState(0);
        return;
    }
    this->getWorld()->dealWithCollisions(this);
    if(this->isDead()){
        return;
    }
}

//============================== Explosion Functions =======================================
void Explosion::doSomething(){
    //if 4 ticks have past, set the explosion to dead
    if(m_ticks>=4){
        this->setState(0);
        return;
    }
    //if it's not the first tick, multiply the size by 1.5
    else if(m_ticks>0){
        this->setSize(this->getSize()*1.5);
    }
    //increment the ticks
    m_ticks++;
}

Explosion::Explosion(StudentWorld * world, int x, int y) :
Actor(world, IID_EXPLOSION, x, y, 0, 1 , 0){
    //initialize ticks to 0
    m_ticks = 0;
}
