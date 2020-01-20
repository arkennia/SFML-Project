#include "explosion.h"
#include "game.h"
#include <string>

Explosion::Explosion()
{
    //enabled = false;
    rotateSpeed = 5;
    type = GameObject::Explosion;
    //init();
    animationSpeed = .4f;
}

void Explosion::animate()
{
    if(!textures->empty())
    {
        //this->rotate(getRotation() + rotateSpeed*Game::getDeltaTime().asSeconds());
        if(animClock.getElapsedTime().asSeconds() >= animationSpeed)
        {
            animClock.restart();
            if(currentImage + 1 == numImages)
            {
                disable();
            }
            else
            {
                currentImage++;
            }
            setTexture(*textures->at(currentImage));
        }
    }
}

void Explosion::init()
{
    std::string path = RESOURCEPATH;
    loadImages(path + "boom", ".png", 3);
}

float Explosion::getRotateSpeed() const
{
    return rotateSpeed;
}

void Explosion::setRotateSpeed(float value)
{
    rotateSpeed = value;
}
