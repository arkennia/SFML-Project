#include "player.h"
#include "projectile.h"

Player::Player() : GameObject()
{
    this->moveSpeed = MOVE_SPEED;
    attack = true;
    attackClock.restart();
    currentAttackSpeed = defaultAttackSpeed;
    lives = 1;
    setType(PC);
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
        p->setOwner(Projectile::Player);
        attackClock.restart();
        return p;
    }
    else return NULL;
}

uint32_t Player::getLives() const
{
    return lives;
}

void Player::death()
{
    lives--;
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
    return attackClock.getElapsedTime().asMilliseconds() >= currentAttackSpeed && enabled;
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

float Player::getCurrentProjectileVelocity() const
{
    return currentProjectileVelocity;
}

void Player::setCurrentProjectileVelocity(float value)
{
    if(value > 0)
        currentProjectileVelocity = value;
}

bool Player::isDead()
{
    return lives <= 0;
}


