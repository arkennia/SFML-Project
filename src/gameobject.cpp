#include "gameobject.h"

GameObject::GameObject() : sf::Sprite()
{
    enable();
    //spriteSheet = NULL;
    textures = NULL;
    currentImage = 0;
    numImages = 0;
    animationSpeed = 1.f;
}

GameObject::GameObject(GameObject::Type type)
{
    this->type = type;
    textures = NULL;
    currentImage = 0;
    numImages = 0;
    animationSpeed = .2f;
    enable();
}

GameObject::~GameObject()
{
//    if(spriteSheet)
//        delete spriteSheet;
    if(textures)
    {
        textures->clear();
        delete textures;
    }
}

void GameObject::initDrawable(std::string path)
{
    this->path = path;
    image.loadFromFile(RESOURCEPATH + path);
    texture.loadFromImage(image);
    this->setTexture(texture);
}

void GameObject::updatePosition(float x_speed, float y_speed, sf::Time elapsed)
{
    this->move(x_speed * elapsed.asSeconds(), y_speed * elapsed.asSeconds());
}

GameObject::Type GameObject::getType() const
{
    return type;
}

void GameObject::setType(const Type &value)
{
    type = value;
}

//sf::IntRect GameObject::getSpriteRect() const
//{
//    return spriteRect;
//}

//void GameObject::setSpriteRect(const sf::IntRect &value)
//{
//    spriteRect = value;
//}

float GameObject::getAnimationSpeed() const
{
    return animationSpeed;
}

void GameObject::setAnimationSpeed(float value)
{
    animationSpeed = value;
}

void GameObject::animate()
{
    if(!textures->empty())
    {
        if(animClock.getElapsedTime().asSeconds() >= this->animationSpeed)
        {
            animClock.restart();
            if(currentImage + 1 == numImages)
            {
                currentImage = 0;
            }
            else
            {
                currentImage++;
            }
            setTexture(*textures->at(currentImage));
        }
    }
}

void GameObject::enable()
{
    enabled = true;
}

void GameObject::disable()
{
    enabled = false;
}

bool GameObject::isEnabled()
{
    return enabled;
}

bool GameObject::shouldAnimate()
{
    return numImages > 0 || textures != NULL;
}

void GameObject::loadImages(std::string name, std::string extension, uint16_t numImages)
{
    sf::Texture *texture;
    textures = new std::vector<sf::Texture *>;
    for(size_t i = 0; i < numImages; i++)
    {
        texture = new sf::Texture();
        texture->loadFromFile(name + std::to_string(i + 1) + extension);
        textures->push_back(texture);
    }
    this->numImages = numImages;
}

//void GameObject::loadImages(std::string path, sf::Vector2i spriteDim, uint16_t numImages)
//{
//    spriteSheet->loadFromFile(path);
//    spriteRect = sf::IntRect(0, 0, spriteDim.x, spriteDim.y);
//    this->numImages = numImages;
//}




