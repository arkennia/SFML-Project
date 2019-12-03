#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SFML/Graphics.hpp>
#include <vector>

#define RESOURCEPATH "resources/"

class Projectile;
class GameObject;
class Graphics
{
public:
    ~Graphics();
    Graphics(sf::RenderWindow &window);
    void render(std::vector<GameObject*> &objs, std::vector<Projectile *> projectiles, GameObject *background);
    void run();
    void createTexture(std::string path, GameObject &obj);    

private:
    sf::RenderWindow *window;
};

#endif // GRAPHICS_H
