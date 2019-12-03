#include "game.h"
#include "graphics.h"
#include "enemy.h"
#include <cstring>

sf::Time Game::deltaTime = sf::Time::Zero;
Game::Game()
{
    scoreNum = 0;
}

Game::~Game()
{
    if(graphics)
        delete graphics;
    if(background)
        delete background;
}

void Game::run()
{
    shouldClose = false;
    gameOver = false;
    init();
    initText();
    Player o = *new Player;
    graphics->createTexture("triangle.png", o);
    o.scale(2.f, 2.f);
    o.setOrigin(16,16);
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
            graphics->render(gameObjects, projectiles, background);
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
        e = reinterpret_cast<Enemy*>(gameObjects[i]);
        if(e->isDead() == false)
        {
            Projectile* p = e->shoot(e->getProjectileSpeed(), e->getCurrentAttackSpeed());
            if(p != NULL)
                projectiles.push_back(p);
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
        graphics->createTexture(texture_path,  *e);
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
                    if(projectiles[i]->getOwner() == Projectile::Enemy)
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
}

void Game::initText()
{
    font.loadFromFile("resources/PLANK___.TTF");
    score.setFont(font);
}

