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

void Graphics::render(std::vector<GameObject *> &objs, std::vector<Projectile*> projectiles, GameObject *background)
{
    window->clear(sf::Color::Black);
    background->animate();//draw background first
    window->draw(*background);
    for (const auto & p : projectiles)
    {
        window->draw(*p);
    }
    for(const auto &g : objs)
    {
        if(g->shouldAnimate())
        {
            g->animate();
        }
        if(g->isEnabled())
            window->draw(*g);
    }
    window->display();
}

void Graphics::createTexture(std::string path, GameObject &obj)
{
    obj.initDrawable(path);
}



