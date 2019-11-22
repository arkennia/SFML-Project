#include "projectile.h"


Projectile::Projectile()
{
    velocity = 100;
    damage = 1;
    attackSpeed = 1;
}

Projectile::~Projectile()
{

}

void Projectile::setDamage(int newDmg)
{
    if(newDmg > 0)
        damage = newDmg;
}

void Projectile::setVelocity(float newVel)
{
    if(newVel > 0)
        velocity = newVel;
}

void Projectile::updatePosition(sf::Time elapsed)
{
    this->move(0, -velocity * elapsed.asSeconds());
}

void Projectile::setAttackSpeed(const uint32_t &value)
{
    if(value > 0)
        attackSpeed = value;
}

int Projectile::getDamage() const
{
    return damage;
}

uint32_t Projectile::getAttackSpeed() const
{
    return attackSpeed;
}
