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
	class Text;
	class Font;
}
class Character;
class Snake;
class Beaver;
class Map;
class AStar;
class Engine;

class WorldManager
{	
	Engine* C_Engine;
	std::list<Character*> observers;
	std::list<std::shared_ptr<Character>> Character_list;
	
	std::list<std::shared_ptr<Snake>> Snake_list;
	
	std::map<std::string, sf::Texture> TextureMap; 
	
	std::shared_ptr<sf::Clock> clock;
	std::shared_ptr<sf::Clock> clock2;
	std::shared_ptr<sf::Clock> SnakeClock;
		
	std::shared_ptr<Beaver> Player;	
	std::shared_ptr<AStar> Star;
	
	std::shared_ptr<sf::Font> p_myFont;
	std::shared_ptr<sf::Text> p_Text;	
	
    std::string map_str = "Textures/map.png";
    std::string potatoFont_str = "Textures/vegetables-field.jpg";
	std::string potato_str = "Textures/potato.png";
	std::string snake_str = "Textures/snake_head.png";
	std::string beaver_str = "Textures/Rat.png";
	
	std::shared_ptr<sf::Sprite> Potato;
	std::shared_ptr<sf::Sprite> PotatoFont;

	float Velocity = 1.f;
	int MaxPotatoes = 3;
	float SpawnTime;
	float SpawnPass = 0.7;
	void DrawScoreAndStoppers(sf::RenderWindow *sf_win);
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
	bool GoToDestination(float goY, float goX, Snake* player);
	void CollideObjects(Character* player);
	void SnakesGoToBeavers();
//	void GoToRandLocation(Snake* player);
	void GoToNearestBeaver(Snake* player);
	void GoToNearestPotato(Snake* player);
	void GoToRandPotato(Snake* player);
	
	void Restart();
	
	void KeyboardEvent(sf::Event event, sf::RenderWindow *sf_win);
	WorldManager(Engine* C_Engine);
};
