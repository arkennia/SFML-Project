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
        Other, //other types, such as projectiles
        Explosion
    };
    GameObject();
    GameObject(Type type);
    virtual ~GameObject();
    void initDrawable(std::string path);
    void updatePosition(float x_speed, float y_speed, sf::Time elapsed);
    Type getType() const;
    void setType(const Type &value);
    void loadImages(std::string name, std::string extension, uint16_t numImages);
    //void loadImages(std::string path, sf::Vector2i spriteDim, uint16_t numImages);

    sf::IntRect getSpriteRect() const;
    void setSpriteRect(const sf::IntRect &value);

    float getAnimationSpeed() const;
    void setAnimationSpeed(float value);

    void animate();

    void enable();
    void disable();
    bool isEnabled();
    bool shouldAnimate();

protected:
    bool enabled;
    Type type;
    std::string path;
    sf::Image image;
    sf::Texture texture;
    //sf::Texture *spriteSheet; //single sprite sheet
    std::vector<sf::Texture *> *textures; //textures for multi-image
    uint16_t currentImage;
    uint16_t numImages;
    //sf::IntRect spriteRect;
    float animationSpeed;
    sf::Clock animClock;
};

#endif // GAMEOBJECT_H
