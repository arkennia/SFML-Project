#include "player.h"
#include "projectile.h"

Player::Player()
{
    this->moveSpeed = MOVE_SPEED;
    attack = true;
    attackClock.restart();
    currentAttackSpeed = defaultAttackSpeed;
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
    if(value > 0)
        moveSpeed = value;
}

Projectile *Player::shoot(int32_t velocity, int32_t attackSpeed)
{
    if(canAttack())
    {
        Projectile *p = new Projectile;
        p->setAttackSpeed(attackSpeed);
        currentAttackSpeed = attackSpeed;
        currentProjectileVelocity = velocity;
        p->setVelocity(velocity);
        p->setDamage(1);
        p->initDrawable(projectile_path);
        p->scale(1.f, 1.f);
        p->setOrigin(16, 16);
        p->setPosition(this->getPosition().x, this->getPosition().y - this->getLocalBounds().height/2);
        attackClock.restart();
        return p;
    }
    else return NULL;
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

bool Player::canAttack()
{
    return attackClock.getElapsedTime().asMilliseconds() >= currentAttackSpeed;
}

int Player::getCurrentAttackSpeed() const
{
    return currentAttackSpeed;
}

void Player::setCurrentAttackSpeed(int value)
{
    if(value > 0)
        currentAttackSpeed = value;
}

int Player::getCurrentProjectileVelocity() const
{
    return currentProjectileVelocity;
}

void Player::setCurrentProjectileVelocity(int value)
{
    if(value > 0)
        currentProjectileVelocity = value;
}


