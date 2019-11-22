#include "player.h"
#include "projectile.h"

Player::Player()
{
    this->moveSpeed = MOVE_SPEED;
}

Player::~Player()
{

}

float Player::getMoveSpeed() const
{
    return moveSpeed;
}

void Player::setMoveSpeed(float value)
{
    moveSpeed = value;
}

Projectile *Player::shoot()
{
    Projectile *p = new Projectile;
    p->setDamage(1);
    p->initDrawable(projectile_path);
    p->scale(1.f, 1.f);
    p->setOrigin(16, 16);
    p->setPosition(this->getPosition().x, this->getPosition().y + this->getLocalBounds().height);
    return p;
}

uint8_t Player::getLives() const
{
    return lives;
}

int Player::death()
{
    lives--;
    return lives;
}

float Player::getProjectileSpeed() const
{
    return projectileSpeed;
}

void Player::setProjectileSpeed(float value)
{
    projectileSpeed = value;
}

