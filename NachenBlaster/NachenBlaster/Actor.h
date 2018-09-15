
#ifndef ACTOR_H_
#define ACTOR_H_
class StudentWorld;
#include "GraphObject.h"
#include "GameConstants.h"

class Actor: public GraphObject{
public:
    Actor(StudentWorld * world, int imageID, int x, int y, int direction, double size, int depth);
    int getName();
    StudentWorld * getWorld();
    void setState(int state);
    int getState();
    bool isDead();
    virtual void sufferCollision(Actor * object) = 0;
    virtual void doSomething() = 0;
    virtual ~Actor(){}
private:
    StudentWorld * studentWorld;
    int m_state; //0 = dead 1 = alive
    int name;
};

#endif // ACTOR_H_

#ifndef NACHENBLASTER_H_
#define NACHENBLASTER_H_

class NachenBlaster : public Actor{
public:
    NachenBlaster(StudentWorld * world);
    virtual void doSomething();
    virtual void sufferCollision(Actor * object);
    int getHealth();
    int getCabbages();
    int getTorpedoes();
    virtual ~NachenBlaster();
private:
    void fireTorpedo();
    void fireCabbage();
    int m_hitpoints;
    int m_cabbage_energy;
    int m_torpedoCount;
};

#endif

#ifndef STAR_H_
#define STAR_H_

class Star : public Actor{
public:
    Star(StudentWorld * world, int x, int y, double size) :
    Actor(world, IID_STAR, x, y, 0, size, 3){}
    virtual void doSomething();
    virtual void sufferCollision(Actor * object){};
    virtual ~Star();
};


#endif


#ifndef ALIEN_H_
#define ALIEN_H_

class Alien : public Actor{
public:
    Alien(StudentWorld * world, int imageID, int flightDirection, double size, int depth, int hitpoints, int flightPlanLen, double travelSpeed);
    void fireProjectile(int name);
    void setFlightDir(int direction);
    int getFlightDir();
    int getFlightPlanLength();
    void setFlightSpeed(double flightSpeed);
    double getFlightSpeed();
    void setFlightPlanLength(int flightPlanLen);
    int getHitpoints();
    void setHitpoints(int hitpoints);
    virtual void sufferCollision(Actor * object) = 0;
    virtual void doSomething() = 0;
private:
    int m_hitpoints;
    double m_travelSpeed;
    int m_flightPlanLen;
    int m_flightDirection;
};

#endif

#ifndef SMALLGON_H_
#define SMALLGON_H_

class Smallgon : public Alien{
public:
    Smallgon(StudentWorld * world, int level) :
    Alien(world, IID_SMALLGON, 0, 1.5, 1, 5*(1+(level-1)*(0.1)), 0, 2.0){}
    virtual void sufferCollision(Actor * object);
    virtual void doSomething();
    virtual ~Smallgon();
};

#endif

#ifndef SMOREGON_H_
#define SMOREGON_H_

class Smoregon : public Alien{
public:
    Smoregon(StudentWorld * world, int level) :
    Alien(world, IID_SMOREGON, 0, 1.5, 1, 5*(1+(level-1)*(0.1)), 0, 2.0){}
    virtual void sufferCollision(Actor * object);
    virtual void doSomething();
    virtual ~Smoregon();
};

#endif

#ifndef SNAGGLEGON_H_
#define SNAGGLEGON_H_

class Snagglegon : public Alien{
public:
    Snagglegon(StudentWorld * world, int level) :
    Alien(world, IID_SNAGGLEGON, -1, 1.5, 1, 10*(1+(level-1)*(0.1)), 0, 1.75){}
    virtual void sufferCollision(Actor * object);
    virtual void doSomething();
    virtual ~Snagglegon();
};


#ifndef PROJECTILE_H_
#define PROJECTILE_H_
class Projectile : public Actor{
public:
    Projectile(StudentWorld * world, int image_ID, int x, int y, int direction, int speed);
    virtual void sufferCollision(Actor * object) {}
    virtual void doSomething();
    virtual ~Projectile() {};
private:
    int m_speed;
};
#endif


#ifndef CABBAGE_H_
#define CABBAGE_H_

class Cabbage : public Projectile{
public:
    Cabbage(StudentWorld * world, int x, int y) :
    Projectile(world, IID_CABBAGE, x, y, 0, 8){}
    virtual ~Cabbage() {}
};


#endif

#ifndef TURNIP_H_
#define TURNIP_H_

class Turnip : public Projectile{
public:
    Turnip(StudentWorld * world, int x, int y) :
    Projectile(world, IID_TURNIP, x, y, 0, -6){}
    virtual ~Turnip() {}
};

#endif

#ifndef FLATULENCE_TORPEDO_H_
#define FLATULENCE_TORPEDO_H_

class F_Torpedo : public Projectile{
public:
    F_Torpedo(StudentWorld * world, int x, int y, int direction) :
    Projectile(world, IID_TORPEDO, x, y, direction, ((direction==0)?8:-8)){}
    virtual ~F_Torpedo() {}
};
#endif

#endif

#ifndef GOODIE_H_
#define GOODIE_H_
class Goodie : public Actor{
public:
    Goodie(StudentWorld * world, int ID,  int x, int y) :
    Actor(world, ID, x, y, 0, 0.5 , 1){}
    virtual void sufferCollision(Actor * object);
    virtual void doSomething();
    virtual ~Goodie(){};
};

#endif

#ifndef REPAIR_GOODIE_H_
#define REPAIR_GOODIE_H_

class R_Goodie : public Goodie{
public:
    R_Goodie(StudentWorld * world, int x, int y) :
    Goodie(world, IID_REPAIR_GOODIE ,x, y){}
    virtual ~R_Goodie(){}
};

#endif

#ifndef EXTRA_LIFE_GOODIE_H_
#define EXTRA_LIFE_GOODIE_H_

class E_Goodie : public Goodie{
public:
    E_Goodie(StudentWorld * world, int x, int y) :
    Goodie(world, IID_LIFE_GOODIE ,x, y){}
    virtual ~E_Goodie(){}
};


#endif

#ifndef FLATULENCE_TORPEDO_GOODIE_H_
#define FLATULENCE_TORPEDO_GOODIE_H_

class T_Goodie : public Goodie{
public:
    T_Goodie(StudentWorld * world, int x, int y) :
    Goodie(world, IID_TORPEDO_GOODIE ,x, y){}
    virtual ~T_Goodie(){}
};


#endif


#ifndef EXPLOSION_H_
#define EXPLOSION_H_

class Explosion : public Actor{
public:
    Explosion(StudentWorld * world, int x, int y);
    virtual void sufferCollision(Actor * object){}
    virtual void doSomething();
    virtual ~Explosion(){}
private:
    int m_ticks;
};

#endif
