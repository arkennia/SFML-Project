#include "graphics.h"
#include "gameobject.h"
#include "projectile.h"
#include "explosion.h"

Graphics::~Graphics()
{
    if(window)
        delete window;
}

Graphics::Graphics(sf::RenderWindow &window)
{
    this->window = &window;
}

void Graphics::render(std::vector<GameObject *> &objs, std::vector<Projectile*> projectiles, GameObject *background, std::vector<sf::Text *> texts)
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
            if(g->getType() == GameObject::Explosion)
            {
                (reinterpret_cast<Explosion*>(g))->animate();
            }
            else
            {
                g->animate();
            }
        }
        if(g->isEnabled())
            window->draw(*g);
    }
    for (const auto & t : texts)
    {
        window->draw(*t);
    }
    window->display();
}

void Graphics::render(sf::Text &text)
{
    window->draw(text);
}

void Graphics::createTexture(std::string path, GameObject &obj)
{
    obj.initDrawable(path);
}

sf::RenderWindow *Graphics::getWindow() const
{
    return window;
}



