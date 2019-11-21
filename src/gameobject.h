#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "graphics.h"

class GameObject : public sf::Sprite
{
    friend class Graphics;
public:
    GameObject();
    void initDrawable(std::string path);
    void updatePosition(float speed, sf::Time elapsed);
private:
    std::string path;
    sf::Image image;
    sf::Texture texture;
};

#endif // GAMEOBJECT_H
