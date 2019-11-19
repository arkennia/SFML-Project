#ifndef GAME_H
#define GAME_H
#define WIDTH 1366
#define HEIGHT 768
#define DEFAULT_FPS 60
#include <iostream>
#include <SFML/Graphics.hpp>
class Graphics;
class Game
{
public:
    //Functions
    Game();
    ~Game();
    void run();
    void cleanup();
private:
    //Constants
    const std::string window_name = "Space Shooter";
    //Game Objects
    Graphics *graphics;
    sf::RenderWindow *window;
};

#endif // GAME_H
