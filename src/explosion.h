#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "gameobject.h"

class Explosion : public GameObject
{
public:
    Explosion();
    void animate();

    float getRotateSpeed() const;
    void setRotateSpeed(float value);
    void init();
private:

    float rotateSpeed; //degrees per s
};

#endif // EXPLOSION_H
