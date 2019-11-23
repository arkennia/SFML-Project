#include "enemy.h"
#include "projectile.h"
Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

Projectile *Enemy::shoot(int32_t velocity, int32_t attackSpeed)
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

bool Enemy::canAttack()
{
    return attackClock.getElapsedTime().asMilliseconds() >= currentAttackSpeed;
}
