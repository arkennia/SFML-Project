#include "gameobject.h"

GameObject::GameObject() : sf::Sprite()
{

}

void GameObject::initDrawable(std::string path)
{
    this->path = path;
    image.loadFromFile(RESOURCEPATH + path);
    texture.loadFromImage(image);
    this->setTexture(texture);
}

void GameObject::updatePosition(float speed, sf::Time elapsed)
{
    this->move(speed * elapsed.asSeconds(), 0.f);
}



