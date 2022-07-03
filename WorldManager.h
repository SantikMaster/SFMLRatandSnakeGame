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
	class Clock;
}
class Character;
class Snake;
class Map;
class AStar;

class WorldManager
{	
	std::list<Character*> observers;
	std::list<std::shared_ptr<Character>> Character_list;
	
	
	std::map<std::string, sf::Texture> TextureMap; 
	
	std::shared_ptr<sf::Clock> clock;
	std::shared_ptr<sf::Clock> clock2;
	std::shared_ptr<Snake> Player;
	
	std::shared_ptr<AStar> Star;
//	std::shared_ptr<Map> WorldMap;
	
	
    std::string map_str = "Textures/map.png";
    std::string potatoFont_str = "Textures/potato_font.png";
	std::string potato_str = "Textures/potato.png";
	std::string snake_str = "Textures/snake_head.png";
	
	std::shared_ptr<sf::Sprite> Potato;
	std::shared_ptr<sf::Sprite> PotatoFont;

	float Velocity = 1.f;
	
	float SpawnTime;
	float SpawnPass = 3;
public:
	void Attach(Character& o) 
	 {
	  observers.push_back(&o); 
	 }
	 void Attach(Character* o) 
	 {
	  observers.push_back(o); 
	 }
    void Detach(Character* o);
	
	static int offsetX;
	static int offsetY;
	
	static Map WorldMap;
	
	template <class T>
	void push_back(T& Object);
	void push_back(int Object);
	void push_back(sf::CircleShape &Obj);
	void push_back(sf::RectangleShape &Obj);
	
	float GetTimeSec();
	int GetTimeMicrosec();
	void Update();
	void Draw(sf::RenderWindow* Window);
	void AI_Move(Character &AI, float time);
	void DrawFont(sf::RenderWindow *sf_win, const sf::Texture &t);
	bool GoToDestination(float goY, float goX);
	void CollideObjects(Character* player);
	void GoToRandLocation();
	void GoToNearestLocation();
	
	void KeyboardEvent(sf::Event event, sf::RenderWindow *sf_win);
	WorldManager();
};
