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
    uint32_t getAttackSpeed() const;
    void setAttackSpeed(const uint32_t &value);
    int getDamage() const;

private:
    //VariablesS
    float velocity;
    int damage;
    uint32_t attackSpeed;
};

#endif 
