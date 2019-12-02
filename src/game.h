#ifndef GAME_H
#define GAME_H

#define WIDTH 640
#define HEIGHT 860
#define DEFAULT_FPS 60


#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "projectile.h"
#include "player.h"

class Graphics;
class Enemy;
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
    bool shouldClose;
    bool gameOver;
    static sf::Time deltaTime;
    const std::string window_name = "Space Shooter";
    //Game Objects
    Graphics *graphics;
    sf::RenderWindow *window;
    std::vector<GameObject*> gameObjects;
    std::vector<Projectile*> projectiles;
    Player *player;
    void handleKeys(sf::Time elapsedTime);
    void updateGameObjects();
    void createEnemies(uint32_t quantity, int32_t moveSpeed, int32_t attackSpeed, uint32_t projectileSpeed, uint32_t lives, std::string texture_path);
    Enemy *createEnemy(int32_t moveSpeed, int32_t attackSpeed, uint32_t projectileSpeed, uint32_t lives);
    void enemyAttack();
    void checkCollisions();
};

#endif // GAME_H
