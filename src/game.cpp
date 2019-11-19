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
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), window_name,sf::Style::Default);
    window->setFramerateLimit(DEFAULT_FPS);
    graphics = new Graphics(*window);
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
                    break;
                default:
                    break;
            }
        }
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
