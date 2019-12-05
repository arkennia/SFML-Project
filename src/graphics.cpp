#include "graphics.h"
#include "gameobject.h"
#include "projectile.h"
#include "explosion.h"
#include <iostream>
Graphics::Texture* Graphics::playerTexture = NULL;
Graphics::Texture* Graphics::playerProjectleTexture = NULL;
Graphics::Texture* Graphics::enemyTexture = NULL;
Graphics::Texture* Graphics::enemyProjectileTexture = NULL;
Graphics::Texture* Graphics::startButton = NULL;
Graphics::Texture* Graphics::enemyTexture2 = NULL;

Graphics::~Graphics()
{
    if(window)
        delete window;
	delete enemyProjectileTexture;
	delete enemyTexture;
	delete playerProjectleTexture;
	delete playerTexture;
	delete startButton;
	delete enemyTexture2;
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

void Graphics::render(sf::Text &text, GameObject &g)
{
	window->clear(sf::Color::Black);
    window->draw(text);
	window->draw(g);
	window->display();
}

void Graphics::createTexture(std::string path, GameObject &obj)
{
    obj.initDrawable(path);
}

Graphics::Texture *Graphics::createTexture(std::string path)
{
	Texture* t = new Texture;
	t->image.loadFromFile(RESOURCEPATH + path);
	t->texture.loadFromImage(t->image);
	return t;
}

Graphics::Texture* Graphics::copyTexture(const Texture& t)
{
	Texture* newT = new Texture;
	newT->image = t.image;
	newT->texture = t.texture;
	return newT;
}

void Graphics::generateTextures()
{
	playerTexture = createTexture("playerShip.png");
	enemyTexture = createTexture("enemyShip.png");
	enemyProjectileTexture = createTexture("enemyLaser.png");
	playerProjectleTexture = createTexture("playerLaser.png");
	startButton = createTexture("startButton.png");
	enemyTexture2 = createTexture("enemyShip2.png");
}

sf::RenderWindow *Graphics::getWindow() const
{
    return window;
}



