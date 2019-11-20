#include "game.h"
#include "graphics.h"
Game::Game()
{

}

Game::~Game()
{
    if(window)
        delete window;
}

void Game::run()
{
    bool should_close = false;
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), window_name,sf::Style::Default);
    window->setFramerateLimit(DEFAULT_FPS);
    graphics = new Graphics(*window);
    GameObject o;
    graphics->createTexture("triangle.png", o);
    gameObjects.push_back(o);
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
    while(window->isOpen())
    {
        sf::Event event;
        while(window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    cleanup();
                    window->close();
                    should_close = true;
                    break;
                default:
                    break;
            }
        }
        if(!should_close)
            graphics->render(gameObjects);
//        window->clear(sf::Color::Black);

//        //draw
//        window->draw(shape);

//        window->display();
    }
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
