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
	struct Texture
	{
		sf::Texture texture;
		sf::Image image;
	};
    ~Graphics();
    Graphics(sf::RenderWindow &window);
    void render(std::vector<GameObject*> &objs, std::vector<Projectile *> projectiles, GameObject *background, std::vector<sf::Text *> texts);
    void render(sf::Text &text);
    void run();
    void createTexture(std::string path, GameObject &obj);   
	Texture* Graphics::createTexture(std::string path);
	Texture* copyTexture(const Texture& t);
	void generateTextures();
    sf::RenderWindow *getWindow() const;
	static Texture* playerTexture;
	static Texture* playerProjectleTexture;
	static Texture *enemyTexture;
	static Texture* enemyProjectileTexture;

private:
    sf::RenderWindow *window;
	
};

#endif // GRAPHICS_H
