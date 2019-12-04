#include "audio.h"
#include "gameobject.h"

Audio::Audio()
{

}

Audio::~Audio()
{
    delete backgroundMusic;
    delete playerShoot;
    delete enemyShoot;
    delete impact;
}

void Audio::playShoot(GameObject &gameObject)
{
    switch(gameObject.getType())
    {
        case GameObject::PC:
        {
            playerShoot->sound.play();
            break;
        }
        case GameObject::EPC:
        {
            enemyShoot->sound.play();
            break;
        }
        default:
        {
            break;
        }
    }
}

void Audio::playImpact()
{
    impact->sound.play();
}

void Audio::init()
{
    backgroundMusic = new Sound;
    impact = new Sound;
    playerShoot = new Sound;
    enemyShoot = new Sound;

    backgroundMusic->buffer.loadFromFile(resourcePath + backgroundPath);
    impact->buffer.loadFromFile(resourcePath + impactPath);
    playerShoot->buffer.loadFromFile(resourcePath + playerPath);
    enemyShoot->buffer.loadFromFile(resourcePath + enemyPath);

    backgroundMusic->sound.setBuffer(backgroundMusic->buffer);
    impact->sound.setBuffer(impact->buffer);
    playerShoot->sound.setBuffer(playerShoot->buffer);
    enemyShoot->sound.setBuffer(enemyShoot->buffer);

    backgroundMusic->sound.setLoop(true);
    backgroundMusic->sound.play();
    backgroundMusic->sound.setVolume(10.f);
    enemyShoot->sound.setVolume(10.f);
}
