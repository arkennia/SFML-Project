#include "game.h"
#include "graphics.h"

sf::Time Game::deltaTime = sf::Time::Zero;
Game::Game()
{

}

Game::~Game()
{
    gameObjects.clear();
}

void Game::run()
{
    shouldClose = false;
    init();
    Player o = *new Player;
    graphics->createTexture("triangle.png", o);
    o.scale(2.f, 2.f);
    o.setOrigin(16,16);
    o.setPosition(WIDTH/2, HEIGHT-o.getLocalBounds().height);
    gameObjects.push_back(&o);
    sf::Clock clock;    
    player = &o;
    while(window->isOpen())
    {
        deltaTime = clock.getElapsedTime();
        clock.restart();
        handleKeys(deltaTime);
        updatePositions();
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
            graphics->render(gameObjects, projectiles);
        }
    }
    cleanup();
}

void Game::cleanup()
{
    if(graphics)
        delete graphics;
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
//        p->setVelocity(MOVE_SPEED);
//        p->setDamage(1);

//        graphics->createTexture("triangle.png", *p);
//        p->scale(1.f, 1.f);
//        p->setOrigin(16, 16);
//        p->setPosition(player.getPosition().x, player.getPosition().y + player.getLocalBounds().height);
        if(p != NULL)
            projectiles.push_back(p);
    }
}

void Game::updatePositions()
{
    for(Projectile *p: projectiles)
    {
        p->updatePosition(deltaTime);
        if(p->isOffScreen())
        {
            projectiles.erase(projectiles.begin());
        }
    }
}
