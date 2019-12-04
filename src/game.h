#ifndef GAME_H
#define GAME_H

#define WIDTH 640
#define HEIGHT 860
#define DEFAULT_FPS 60
#define LEVEL1 1
#define LEVEL2 20
#define LEVEL3 60
#define LEVEL4 120
#define LEVEL5 200

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "gameobject.h"
#include "projectile.h"
#include "player.h"

class Audio;
class Graphics;
class Enemy;
class Game
{
public:
    //Functions
    Game();
    ~Game();
    void run();
    void testRun();
    void cleanup();
    void addGameObject(GameObject &object);
    void init();

    static sf::Time getDeltaTime();

    friend class TestClass;
private:

    //Constants
    bool shouldClose;
    bool gameOver;
    static sf::Time deltaTime;
    const std::string window_name = "Space Shooter";
    //Game Objects
    std::vector<GameObject*> gameObjects;
    std::vector<Projectile*> projectiles;
    std::vector<sf::Text *> texts;

    void handleKeys(sf::Time elapsedTime);
    void updateGameObjects();
    void createEnemies(uint32_t quantity, int32_t moveSpeed, int32_t attackSpeed, uint32_t projectileSpeed, uint32_t lives, std::string texture_path);
    Enemy *createEnemy(int32_t moveSpeed, int32_t attackSpeed, uint32_t projectileSpeed, uint32_t lives);
    void enemyAttack();
    void checkCollisions();
    void initText();
    void spawnEnemy();
    void restart();
    void manageLevel();

    sf::Clock spawnTimer;
    float spawnSpeed = 4;
    uint32_t spawnQuantity;
    int totalSpawnedEnemies;
    std::string currentLevel;
    int scoreNum;
    int fireChance;
    sf::Font *font;
    sf::Text *score;
    sf::Text *lives;
    sf::Text *gameDone;
    sf::Text *level;
    Audio *audio;
    Player *player;
    GameObject *background;
    Graphics *graphics;
    sf::RenderWindow *window;
};

#endif // GAME_H
