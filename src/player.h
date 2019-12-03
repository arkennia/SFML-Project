#ifndef PLAYER_H
#define PLAYER_H
#define MOVE_SPEED 500

#include <cstdint>
#include "gameobject.h"

class Projectile;
class Player : public GameObject
{
public:
    Player();
    ~Player();
    float getMoveSpeed() const;
    void setMoveSpeed(float value);
    Projectile* shoot(int32_t velocity = defaultProjectileVelocity, int32_t attackSpeed = defaultAttackSpeed);
    uint32_t getLives() const;
    void death();
    float getProjectileSpeed() const;
    void setProjectileSpeed(float value);
    bool canAttack();
    int getCurrentAttackSpeed() const;
    void setCurrentAttackSpeed(int value);
    float getCurrentProjectileVelocity() const;
    void setCurrentProjectileVelocity(float value);
    bool isDead();

protected:
    static const int32_t defaultAttackSpeed = 300;
    static const int32_t defaultProjectileVelocity = 300;
    int currentAttackSpeed;
    float currentProjectileVelocity;
    const std::string projectile_path = "triangle.png";
    uint32_t lives;
    float moveSpeed;
    float projectileSpeed;
    sf::Clock attackClock;
    bool attack;
};

#endif // PLAYER_H
