#include "projectile.h"
#include "game.h"

Projectile::Projectile()
{
    velocity = 100;
    damage = 1;
    attackSpeed = 1;
    setType(Other);
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
        velocity = newVel;
}

void Projectile::updatePosition(sf::Time elapsed)
{
	lastPositon = getPosition();
    this->move(0, -velocity * elapsed.asSeconds());
}

void Projectile::setAttackSpeed(const int32_t &value)
{
    if(value > 0)
        attackSpeed = value;
}

int Projectile::getDamage() const
{
    return damage;
}

bool Projectile::isOffScreen()
{
    return this->getPosition().y < 0 || this->getPosition().y > HEIGHT;
}

float Projectile::getVelocity() const
{
	return velocity;
}

sf::Vector2f Projectile::getLastPosition()
{
	return lastPositon;
}

Projectile::Owner Projectile::getOwner() const
{
    return o;
}

void Projectile::setOwner(const Owner &value)
{
    o = value;
}

int32_t Projectile::getAttackSpeed() const
{
    return attackSpeed;
}
