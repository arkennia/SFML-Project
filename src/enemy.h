#ifndef ENEMY_H
#define ENEMY_H
#include "player.h"
#include <SFML/Graphics.hpp>

class Enemy : public Player
{
public:
    Enemy();
    ~Enemy();
    Projectile *shoot(float velocity, int32_t attackSpeed);
    bool canAttack();
    void setLives(uint32_t value);
    void takeDamage(uint16_t damage);


    sf::Vector2f getSpawnPoint() const;
    void setSpawnPoint(const sf::Vector2f &value);

private:
    sf::Vector2f spawnPoint;
};

#endif // ENEMY_H
