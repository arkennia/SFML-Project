#include "game.h"
#include "graphics.h"
#include "enemy.h"
#include "audio.h"
#include <cstring>
#include <random>
#include <thread>
#include "explosion.h"
#include "testclass.h"

sf::Time Game::deltaTime = sf::Time::Zero;
Game::Game()
{
    scoreNum = 0;
    totalSpawnedEnemies = 0;
    spawnTimer.restart();
    audio = NULL;
    font = NULL;
    score = NULL;
    lives = NULL;
    gameDone = NULL;
    audio = NULL;
    player = NULL;
    background = NULL;
    graphics = NULL;
    window = NULL;
}

Game::~Game()
{
    if(graphics)
        delete graphics;
    if(background)
        delete background;
    if(score)
        delete score;
    if(font)
        delete font;
    if(lives)
        delete lives;
    delete level;
    texts.clear();
    delete audio;
}

/*
 *  Runs the game. Checks for collisions, handles key pushs, spawns enemies once per frame.
 */
void Game::run()
{
    srand(std::time(0));
    shouldClose = false;
    gameOver = false;
    init();
    //initText();
    sf::Clock clock;      
    while(window->isOpen())
    {
        deltaTime = clock.getElapsedTime();
        clock.restart();
        handleKeys(deltaTime);
        checkCollisions();
        updateGameObjects();
        manageLevel();
        if(gameOver)
        {
            //std::cerr << "Game over!" << std::endl;
            if(gameObjects.empty() == false)
                gameObjects.clear();
            if(projectiles.empty() == false)
            {
                projectiles.clear();
                texts.push_back(gameDone);
            }
        }
        else spawnEnemy();
        sf::Event event;
        while(window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    shouldClose = true;
                    break;
                default:
                    break;
            }
            if(shouldClose)
            {
                window->close();
            }            
        }
        if(!shouldClose)
        {
            score->setString("Score: " + std::to_string(scoreNum));
            graphics->render(gameObjects, projectiles, background, texts);
        }
    }
    cleanup();
}

void Game::testRun()
{
    bool testCol = false;
    TestClass t;
    srand(std::time(0));
    shouldClose = false;
    gameOver = false;
    init();
    //initText();
    sf::Clock clock;
    while(window->isOpen())
    {
        deltaTime = clock.getElapsedTime();
        clock.restart();
        //handleKeys(deltaTime);

        checkCollisions();
        updateGameObjects();
        //manageLevel();

        if(gameOver)
        {
            //std::cerr << "Game over!" << std::endl;
            if(gameObjects.empty() == false)
                gameObjects.clear();
            if(projectiles.empty() == false)
            {
                projectiles.clear();
                texts.push_back(gameDone);
            }
        }
        //else spawnEnemy();
        sf::Event event;
        while(window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    shouldClose = true;
                    break;
                default:
                    break;
            }
            if(shouldClose)
            {
                window->close();
            }
        }
        if(!shouldClose)
        {
            score->setString("Score: " + std::to_string(scoreNum));
            graphics->render(gameObjects, projectiles, background, texts);
        }
        if(!testCol)
        {
            testCol = true;
            t.testCollision(*this);
            t.testScore(*this);
        }
        t.testMovement(*this);
    }
    cleanup();
}
/*
 * Clean up the two vectors
 */
void Game::cleanup()
{
    gameObjects.clear();
    projectiles.clear();
    texts.clear();
}


/*
 * Adds a game object...a bit redundant
 */
void Game::addGameObject(GameObject &object)
{
    gameObjects.push_back(&object);
}

/*
 * Create the window and pass it to the graphics module
 */
void Game::init()
{
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), window_name, sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(DEFAULT_FPS);
    graphics = new Graphics(*window);
    audio = new Audio;
    audio->init();
    restart();
}

/*
 *  Returns the time since last frame
 */
sf::Time Game::getDeltaTime()
{
    return deltaTime;
}


/*
 * Handles key input
 * Shoot: Click, Space
 * Move WASD/Arrow keys
 */
void Game::handleKeys(sf::Time elapsedTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
        if (player->getPosition().x >= 15)
        {
            player->updatePosition(-player->getMoveSpeed(), 0, elapsedTime);

            if (player->getPosition().x < 15)
            {
                player->setPosition(15, player->getPosition().y);
            }
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
        if (player->getPosition().x <= WIDTH - 16)
        {
            player->updatePosition(player->getMoveSpeed(), 0, elapsedTime);
            if (player->getPosition().x > WIDTH - 16)
            {
                player->setPosition(WIDTH - 16, player->getPosition().y);
			}

		}
	}
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        shouldClose = true;
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//shoot
        Projectile *p = player->shoot();
        if(p != NULL)
        {
            projectiles.push_back(p);
            audio->playShoot(*player);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        //restart
        if(gameOver)
        {
            restart();
        }
    }
}

/*
 * Checks if player is dead, return if true
 * Update the position of the projectiles and check if they are offscreen
 * Enemies shoot
 */
void Game::updateGameObjects()
{
    if(player->isDead() && player->isEnabled())
    {
        gameOver = true;
        player->disable();
        return;
    }
    else
    {
        if(player->getLives() >= 0)
        {
            lives->setString("Lives: " + std::to_string(player->getLives()));
        }
        else
        {
            lives->setString("Lives: 0");
        }
    }
    for(size_t i = 0; i < projectiles.size(); i++)
    {
        projectiles[i]->updatePosition(deltaTime);
        if(projectiles[i]->isOffScreen())
        {
            projectiles.erase(projectiles.begin() + i);
        }
    }
    Enemy *e;
    for(size_t i = 1; i < gameObjects.size(); i++)
    {
        fireChance = rand() % 60 + 1;
        e = reinterpret_cast<Enemy*>(gameObjects[i]);
        if(e->isDead() == false)
        {
            if(fireChance == 20)
            {
                Projectile* p = e->shoot(e->getProjectileSpeed(), e->getCurrentAttackSpeed());
                if(p != NULL)
                {
                    projectiles.push_back(p);
                    audio->playShoot(*e);
                }
            }
        }
        else if(e->getType() == GameObject::EPC)
        {
            scoreNum += e->getScoreValue();
            Explosion *explosion = new Explosion;
            explosion->init();
            explosion->setPosition(e->getPosition());
            gameObjects.push_back(explosion);
            gameObjects.erase(gameObjects.begin() + i);
        }
    }
}

/*
 * Create enemies at a random position
 */
void Game::createEnemies(uint32_t quantity, int32_t moveSpeed, int32_t attackSpeed, uint32_t projectileSpeed, uint32_t lives, std::string texture_path)
{
    Enemy *e;
    for(size_t i = 0; i < quantity; i++)
    {
        e = createEnemy(moveSpeed, attackSpeed, projectileSpeed, lives);
        e->setPosition(rand() % WIDTH, rand() % (HEIGHT - 300));
        graphics->createTexture(texture_path,  *e);
        e->setOrigin(e->getLocalBounds().width/2 ,e->getLocalBounds().height/2);
        gameObjects.push_back(e);
    }
}

/*
 * Create a single enemy
 */
Enemy *Game::createEnemy(int32_t moveSpeed, int32_t attackSpeed, uint32_t projectileSpeed, uint32_t lives)
{
    Enemy *e = new Enemy;    
    e->setLives(lives);
    e->setProjectileSpeed(projectileSpeed);
    e->setCurrentAttackSpeed(attackSpeed);
    e->setMoveSpeed(moveSpeed);
    totalSpawnedEnemies++;
    return e;
}

/*
 * Check the collisios by looking at the bounding boxes of the textures. Normally this wouldn't work...
 */
void Game::checkCollisions()
{

    for(auto &gameO : gameObjects)
    {
        for(size_t i = 0; i < projectiles.size(); i++)
        {
            if(projectiles[i]->getGlobalBounds().intersects(gameO->getGlobalBounds()))
            {
                if(projectiles[i]->getOwner() == Projectile::Player)
                {
                    if(gameO->getType() == GameObject::EPC)
                    {
                        Enemy *e = reinterpret_cast<Enemy*>(gameO);
                        e->takeDamage(projectiles[i]->getDamage());
                        projectiles.erase(projectiles.begin() + i);
                    }
                }
                else if(projectiles[i]->getOwner() == Projectile::Enemy)
                {                   
                    if(gameO->getType() == GameObject::PC)
                    {
                        Player *p = reinterpret_cast<Player*>(gameO);
                        p->death();
                        projectiles.erase(projectiles.begin() + i);
                    }
                }
                audio->playImpact();
            }
        }
    }
}

void Game::initText()
{
    font = new sf::Font;
    score = new sf::Text;
    font->loadFromFile("resources/PLANK___.TTF");
    score->setFont(*font);
    score->setCharacterSize(24);
    score->setFillColor(sf::Color::White);
    texts.push_back(score);
    gameDone = new sf::Text;
    gameDone->setString("Game Over! :(");
    gameDone->setFont(*font);
    gameDone->setCharacterSize(64);
    gameDone->setPosition(0, HEIGHT/2);
    lives = new sf::Text;
    lives->setFont(*font);
    lives->setCharacterSize(24);
    lives->setFillColor(sf::Color::White);
    lives->setPosition(0, HEIGHT - 24);
    level = new sf::Text;
    level->setFont(*font);
    level->setCharacterSize(24);
    level->setFillColor(sf::Color::White);
    level->setString("Level 1");
    level->setPosition(WIDTH - (level->getLocalBounds().width + 4), 0);
    texts.push_back(level);
    texts.push_back(lives);

}

void Game::spawnEnemy()
{
    if(spawnTimer.getElapsedTime().asSeconds() >= spawnSpeed)
    {
        createEnemies(spawnQuantity, 300, 1000, 500, 1, "enemy.png");
        spawnTimer.restart();
    }
}

void Game::restart()
{
    gameObjects.clear();
    projectiles.clear();
    texts.clear();
    Player *o = new Player;
    o->setLives(2);
    graphics->createTexture("triangle.png", *o);
    o->setColor(sf::Color::Blue);
    o->scale(2.f, 2.f);
    o->setOrigin(o->getLocalBounds().width/2,o->getLocalBounds().height/2);
    o->setPosition(WIDTH/2, HEIGHT-(o->getLocalBounds().height + 24));
    gameObjects.push_back(o);
    background = new GameObject(GameObject::Other);
    background->loadImages("resources/starBackground", ".png", 3);
    createEnemies(1, 500, 1000, 300, 1, "enemy.png");
    player = o;
    initText();
    shouldClose = false;
    gameOver = false;
    spawnTimer.restart();
    scoreNum = 0;
}

void Game::manageLevel()
{
    if(totalSpawnedEnemies == LEVEL1 && currentLevel != "Level 1")
    {
        spawnSpeed = 5.f;
        currentLevel = "Level 1";
        level->setString(currentLevel);
        player->setLives(player->getLives() + 1);
    }
    else if(totalSpawnedEnemies == LEVEL2 && currentLevel != "Level 2")
    {
        spawnSpeed = 3.7f;
        spawnQuantity = 2;
        currentLevel = "Level 2";
        level->setString(currentLevel);
        player->setLives(player->getLives() + 1);
    }
    else if(totalSpawnedEnemies == LEVEL3 && currentLevel != "Level 3")
    {
        spawnSpeed = 3.f;
        currentLevel = "Level 3";
        level->setString(currentLevel);
        player->setLives(player->getLives() + 1);
    }
    else if(totalSpawnedEnemies == LEVEL4 && currentLevel != "Level 4")
    {
        spawnSpeed = 2.f;
        currentLevel = "Level 4";
        spawnQuantity = 3;
        level->setString(currentLevel);
        player->setLives(player->getLives() + 1);
    }
    else if(totalSpawnedEnemies == LEVEL5 && currentLevel != "Level 5")
    {
        spawnSpeed = 1.f;
        currentLevel = "Level 5";
        level->setString(currentLevel);
        player->setLives(player->getLives() + 1);
    }
}

