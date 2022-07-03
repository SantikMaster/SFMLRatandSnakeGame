#include <list>
#include <memory>
namespace sf
{
	class RenderWindow;
	class CircleShape;
	class RectangleShape;
	class Texture;
	class Sprite;
	class Event;
}
class Character;
class Snake;

class WorldManager
{
	std::map<std::string, sf::Texture> TextureMap; 
	std::shared_ptr<Snake> Player;
	
    std::string map_str = "Textures/map.png";
	std::string elf_str = "Textures/pngegg (2).png";
	std::string mush_str = "Textures/mush.png";
	std::string vic_str = "Textures/victory.png";
	std::string defeat_str = "Textures/defeat.jpg";
	std::string snake_str = "Textures/snake_head.png";
	
	
    std::shared_ptr<sf::Sprite> Cloud;
    std::shared_ptr<sf::Sprite>	Cloud2;
    std::shared_ptr<sf::Sprite> Tree;
	std::shared_ptr<sf::Sprite>	Tree2;
    std::shared_ptr<sf::Sprite> Sun;
	float Velocity = 1.f;
	
public:
	static int offsetX;
	static int offsetY;
	
	template <class T>
	void push_back(T& Object);
	void push_back(int Object);
	void push_back(sf::CircleShape &Obj);
	void push_back(sf::RectangleShape &Obj);
	
	void Update();
	void Draw(sf::RenderWindow* Window);
	void AI_Move(Character &AI, float time);
	void DrawFont(sf::RenderWindow *sf_win, const sf::Texture &t);
	
	void KeyboardEvent(sf::Event event);
	WorldManager();
};
