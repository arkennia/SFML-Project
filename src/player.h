#ifndef PLAYER_H
#define PLAYER_H
#define MOVE_SPEED 500

#include "gameobject.h"

class Projectile;
class Player : public GameObject
{
public:
    Player();
    ~Player();
    float getMoveSpeed() const;
    void setMoveSpeed(float value);
    Projectile* shoot();
    uint8_t getLives() const;
    int death();
    float getProjectileSpeed() const;
    void setProjectileSpeed(float value);

private:
    const std::string projectile_path = "triangle.png";
    uint8_t lives;
    float moveSpeed;
    float projectileSpeed;
};

#endif // PLAYER_H
