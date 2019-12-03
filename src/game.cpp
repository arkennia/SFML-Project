#include "game.h"
#include "graphics.h"
#include "enemy.h"
#include <cstring>
#include <random>
#include <thread>

sf::Time Game::deltaTime = sf::Time::Zero;
Game::Game()
{
    scoreNum = 0;
    spawnTimer.restart();
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
}

void Game::run()
{
    srand(std::time(0));
    shouldClose = false;
    gameOver = false;
    init();
    initText();
    Player o = *new Player;
    graphics->createTexture("triangle.png", o);
    o.scale(2.f, 2.f);
    o.setOrigin(o.getLocalBounds().width/2,o.getLocalBounds().height/2);
    o.setPosition(WIDTH/2, HEIGHT-o.getLocalBounds().height);
    gameObjects.push_back(&o);
    background = new GameObject(GameObject::Other);
    background->loadImages("resources/starBackground", ".png", 3);
    createEnemies(1, 500, 1000, 300, 1, "enemy.png");    
    sf::Clock clock;    
    player = &o;    
    while(window->isOpen())
    {
        deltaTime = clock.getElapsedTime();
        clock.restart();
        handleKeys(deltaTime);
        checkCollisions();
        updateGameObjects();
        if(gameOver)
        {
            std::cerr << "Game over!" << std::endl;
            gameObjects.clear();
            projectiles.clear();
            gameOver = false;
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

void Game::cleanup()
{
    gameObjects.clear();
    projectiles.clear();
}

void Game::addGameObject(GameObject &object)
{
    gameObjects.push_back(&object);
}

void Game::init()
{
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), window_name, sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(DEFAULT_FPS);
    graphics = new Graphics(*window);
}

sf::Time Game::getDeltaTime()
{
    return deltaTime;
}

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
            projectiles.push_back(p);
    }
}

void Game::updateGameObjects()
{
    if(player->isDead() && player->isEnabled())
    {
        gameOver = true;
        player->disable();
        return;
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
        fireChance = rand() % 50 + 1;
        e = reinterpret_cast<Enemy*>(gameObjects[i]);
        if(e->isDead() == false)
        {
            if(fireChance == 20)
            {
                Projectile* p = e->shoot(e->getProjectileSpeed(), e->getCurrentAttackSpeed());
                if(p != NULL)
                    projectiles.push_back(p);
            }
        }
        else
        {
            scoreNum += e->getScoreValue();
            gameObjects.erase(gameObjects.begin() + i);
        }
    }
}

void Game::createEnemies(uint32_t quantity, int32_t moveSpeed, int32_t attackSpeed, uint32_t projectileSpeed, uint32_t lives, std::string texture_path)
{
    Enemy *e;
    for(size_t i = 0; i < quantity; i++)
    {
        e = createEnemy(moveSpeed, attackSpeed, projectileSpeed, lives);
        e->setPosition(random() % WIDTH, random() % (HEIGHT - 300));
        graphics->createTexture(texture_path,  *e);
        e->setOrigin(e->getLocalBounds().width/2 ,e->getLocalBounds().height/2);
        gameObjects.push_back(e);
    }
}

Enemy *Game::createEnemy(int32_t moveSpeed, int32_t attackSpeed, uint32_t projectileSpeed, uint32_t lives)
{
    Enemy *e = new Enemy;    
    e->setLives(lives);
    e->setProjectileSpeed(projectileSpeed);
    e->setCurrentAttackSpeed(attackSpeed);
    e->setMoveSpeed(moveSpeed);
    return e;
}

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
}

void Game::spawnEnemy()
{
    if(spawnTimer.getElapsedTime().asSeconds() >= spawnSpeed)
    {
        createEnemies(1, 300, 1000, 200, 1, "enemy.png");
        spawnTimer.restart();
    }
}

