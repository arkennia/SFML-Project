#include "graphics.h"

Graphics::Graphics(sf::RenderWindow &window)
{
    this->window = &window;
}

void Graphics::createTexture(std::string path, Sprite &sprite)
{
    sprite.path = path;
    sprite.image.loadFromFile(resource_path + "triangle.png");
    sprite.texture.loadFromImage(sprite.image);
    sprite.sprite.setTexture(sprite.texture);
}


