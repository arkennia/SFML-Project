#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SFML/Graphics.hpp>
#include <vector>

class GameObject;
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
    ~Graphics();
    Graphics(sf::RenderWindow &window);
    void render(const std::vector<GameObject> &objs);
    void run();
    void createTexture(std::string path, GameObject &obj);

private:
    sf::RenderWindow *window;
};

#endif // GRAPHICS_H
