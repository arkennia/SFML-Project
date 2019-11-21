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
        window->draw(g);
    }
    window->display();
}

void Graphics::createTexture(std::string path, GameObject &obj)
{
    obj.initDrawable(path);
}



