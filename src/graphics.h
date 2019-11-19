#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SFML/Graphics.hpp>
class Graphics
{
public:
    const std::string resource_path = "resources/";
    struct Sprite
    {
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Image image;
        std::string path;
    };
    Graphics(sf::RenderWindow &window);
    void run();
    void createTexture(std::string path, Sprite &sprite);

private:
    sf::RenderWindow *window;
};

#endif // GRAPHICS_H
