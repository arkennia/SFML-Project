#ifndef GAME_H
#define GAME_H

#define WIDTH 640
#define HEIGHT 860
#define DEFAULT_FPS 60
#define MOVE_SPEED 500

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "projectile.h"

class Graphics;
class Game
{
public:
    //Functions
    Game();
    ~Game();
    void run();
    void cleanup();
    void addGameObject(GameObject &object);
    void init();

    static sf::Time getDeltaTime();

private:
    //Constants
    static sf::Time deltaTime;
    const std::string window_name = "Space Shooter";
    //Game Objects
    Graphics *graphics;
    sf::RenderWindow *window;
    std::vector<GameObject*> gameObjects;
    std::vector<Projectile*> projectiles;
    GameObject *player;
    void handleKeys(GameObject &player, sf::Time elapsedTime);
    void updatePositions();
};

#endif // GAME_H
