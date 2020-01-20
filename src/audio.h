#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>

class GameObject;
class Audio
{
public:
    Audio();
    ~Audio();
    void playShoot(GameObject &gameObject);
    void playImpact();
    const std::string resourcePath = "resources/";
    void init();

private:
    struct Sound
    {
        sf::SoundBuffer buffer;
        sf::Sound sound;
    };
    const std::string enemyPath = "enemy_shoot.wav";
    const std::string playerPath = "player_shoot.wav";
    const std::string impactPath = "hit.wav";
    const std::string backgroundPath = "background_music.ogg";
    Sound *backgroundMusic;
    Sound *enemyShoot;
    Sound *playerShoot;
    Sound *impact;
};

#endif // AUDIO_H
