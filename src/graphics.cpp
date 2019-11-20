#include "graphics.h"
#include "gameobject.h"
Graphics::~Graphics()
{
    if(window)
        delete window;
}

Graphics::Graphics(sf::RenderWindow &window)
{
    this->window = &window;
}

void Graphics::render(const std::vector<GameObject> &objs)
{
    window->clear(sf::Color::Black);
    for(const auto &g : objs)
    {
        window->draw(g.sprite.sprite);
    }
    window->display();
}

void Graphics::createTexture(std::string path, GameObject &obj)
{
    obj.sprite.path = path;
    obj.sprite.image.loadFromFile(resource_path + path);
    obj.sprite.texture.loadFromImage(obj.sprite.image);
    obj.sprite.sprite.setTexture(obj.sprite.texture);
}


