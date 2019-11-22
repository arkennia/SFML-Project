#include "game.h"
#include "graphics.h"

Game::Game()
{

}

Game::~Game()
{
    gameObjects.clear();
}

void Game::run()
{
    bool should_close = false;
    init();
    GameObject o = *new GameObject;
    graphics->createTexture("triangle.png", o);
    o.scale(2.f, 2.f);
    o.setOrigin(16,16);
    o.setPosition(WIDTH/2, HEIGHT-o.getLocalBounds().height);
    gameObjects.push_back(o);
    sf::Clock clock;
    sf::Time deltaTime;
    player = &gameObjects[0];
    while(window->isOpen())
    {
        deltaTime = clock.getElapsedTime();
        clock.restart();
        handleKeys(*player, deltaTime);
        sf::Event event;
        while(window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    should_close = true;
                    break;
                default:
                    break;
            }
        }
        if(!should_close)
            graphics->render(gameObjects);
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
    gameObjects.push_back(object);
}

void Game::init()
{
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), window_name, sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(DEFAULT_FPS);
    graphics = new Graphics(*window);
}

void Game::handleKeys(GameObject& player, sf::Time elapsedTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (player.getPosition().x >= 15) {
			player.updatePosition(-MOVE_SPEED, elapsedTime);
			
			if (player.getPosition().x < 15)
				player.setPosition(15, player.getPosition().y);
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (player.getPosition().x <= WIDTH - 16) {
			player.updatePosition(MOVE_SPEED, elapsedTime);

			if (player.getPosition().x > WIDTH - 16) {
				player.setPosition(WIDTH - 16, player.getPosition().y);
			}

		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//shoot

		Projectile p = * new Projectile;

		p.setVel(MOVE_SPEED);
		p.setDmg(1);

		graphics->createTexture("triangle.png", p);
		p.scale(1.f, 1.f);
		p.setOrigin(16, 16);
		p.setPosition(player.getPosition());
		gameObjects.push_back(p);
	}
}