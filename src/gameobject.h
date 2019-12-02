#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "graphics.h"

class GameObject : public sf::Sprite
{
    friend class Graphics;
public:
    enum Type
    {
        PC, //player character
        EPC, //enemy (non) player character
        NPC,//non player character
        Other //other types, such as projectiles
    };
    GameObject();
    void initDrawable(std::string path);
    void updatePosition(float x_speed, float y_speed, sf::Time elapsed);
    Type getType() const;
    void setType(const Type &value);

protected:
    Type type;
    std::string path;
    sf::Image image;
    sf::Texture texture;
};

#endif // GAMEOBJECT_H
