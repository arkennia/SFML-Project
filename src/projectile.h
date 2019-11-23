#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameobject.h"
#include <cstdint>

class Projectile : public GameObject
{
public:
    //Constructors
    Projectile();
    ~Projectile();

    //Functions
    void setDamage(int newDmg);
    void setVelocity(float newVel);
    void updatePosition(sf::Time elapsed);
    int32_t getAttackSpeed() const;
    void setAttackSpeed(const int32_t &value);
    int getDamage() const;
    bool isOffScreen();

private:
    //VariablesS
    float velocity;
    int damage;
    int32_t attackSpeed;
};

#endif 
