#include "projectile.h"


Projectile::Projectile()
{
    velocity = 100;
    damage = 1;
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
