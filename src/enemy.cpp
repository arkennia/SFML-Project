#include "enemy.h"
#include "projectile.h"
#include "game.h"
Enemy::Enemy() : Player()
{
    spawnPoint = sf::Vector2f(WIDTH/2, HEIGHT /2);
    this->setPosition(spawnPoint);
    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
    scale(2.f, 2.f);
    setType(EPC);
    scoreValue = 10;
}

Enemy::~Enemy()
{

}

Projectile *Enemy::shoot(float velocity, int32_t attackSpeed)
{
    if(canAttack())
    {
        Projectile *p = new Projectile;
        p->setAttackSpeed(attackSpeed);
        currentAttackSpeed = attackSpeed;
        currentProjectileVelocity = -velocity;
        p->rotate(180.f);
        p->setVelocity(currentProjectileVelocity);
        p->setDamage(1);
        p->initDrawable(projectile_path);
        p->scale(1.f, 1.f);
        p->setOrigin(p->getLocalBounds().width/2, p->getLocalBounds().height/2);
        p->setPosition(this->getPosition().x, this->getPosition().y);
        p->setOwner(Projectile::Enemy);
        attackClock.restart();
        return p;
    }
    else return NULL;
}

bool Enemy::canAttack()
{
    return attackClock.getElapsedTime().asMilliseconds() >= currentAttackSpeed;
}

void Enemy::setLives(uint32_t value)
{
    if(this->lives > value)
        this->lives = value;
}

void Enemy::takeDamage(uint16_t damage)
{
    lives -= damage;
}

sf::Vector2f Enemy::getSpawnPoint() const
{
    return spawnPoint;
}

void Enemy::setSpawnPoint(const sf::Vector2f &value)
{
    spawnPoint = value;
}

int Enemy::getScoreValue() const
{
    return scoreValue;
}

void Enemy::setScoreValue(int value)
{
    scoreValue = value;
}

