#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameobject.h"

class Projectile : public GameObject
{
private:
	float velocity;
	int damage;
public:
    Projectile();
    ~Projectile();
    void setDamage(int newDmg);
    void setVelocity(float newVel);
    void updatePosition(sf::Time elapsed);
};

#endif 
