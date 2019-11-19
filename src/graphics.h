#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SFML/Graphics.hpp>
class Graphics
{
public:
    Graphics(sf::RenderWindow &window);
    void run();

private:
    sf::RenderWindow *window;
};

#endif // GRAPHICS_H
