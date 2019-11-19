#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "graphics.h"
class GameObject
{
    friend class Graphics;
public:
    GameObject();
    void draw();
    void updatePosition(sf::Vector2<float> pos);
    void moveRelative(sf::Vector2<float> offset);
    void updateRotation(float angle);
    void rotateRelative(float offset);
    void updateScale(sf::Vector2<float> scale);
    void scaleRelative(sf::Vector2<float> offset);
    void setOrigin(sf::Vector2<float> origin);
private:
    Graphics::Sprite *sprite;
};

#endif // GAMEOBJECT_H
