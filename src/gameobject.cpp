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

void GameObject::updatePosition(float x_speed, float y_speed, sf::Time elapsed)
{
    this->move(x_speed * elapsed.asSeconds(), y_speed * elapsed.asSeconds());
}



