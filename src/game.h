#ifndef GAME_H
#define GAME_H
#define WIDTH 768
#define HEIGHT 1366
#define DEFAULT_FPS 60
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "gameobject.h"
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
private:
    //Constants
    const std::string window_name = "Space Shooter";
    //Game Objects
    Graphics *graphics;
    sf::RenderWindow *window;
    std::vector<GameObject> gameObjects;
};

#endif // GAME_H
