#include "graphics.h"
#include "gameobject.h"
#include "projectile.h"
Graphics::~Graphics()
{
    if(window)
        delete window;
}

Graphics::Graphics(sf::RenderWindow &window)
{
    this->window = &window;
}

void Graphics::render(std::vector<GameObject *> &objs, std::vector<Projectile*> projectiles)
{
    window->clear(sf::Color::Black);
    for(const auto &g : objs)
    {
        window->draw(*g);
    }
    for (const auto & p : projectiles)
    {
        window->draw(*p);
    }
    window->display();
}

void Graphics::createTexture(std::string path, GameObject &obj)
{
    obj.initDrawable(path);
}



