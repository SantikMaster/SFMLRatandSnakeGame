#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
struct Section
{
	int X, Y;
	bool Horizontal;
};
namespace sf
{
	class Time;
	class Texture;
}
class Map;
class WorldManager;
class Character
{

	
public:	
    WorldManager * World;
	
	static int Amount;
	int Counter = 0;
	float X = 0, Y = 0, dX = 0, dY = 0;
	int Width = 0;
	int Height = 0;
	bool OnGround = true;
	bool AI_LeftMove = false;
	
	bool IsPathAvaible = false;
	int PickedPotato = 0;
	
	float SpawnTime;
	
	virtual void update(float time);
	virtual void draw(sf::RenderWindow *sf_win);
	
	Character(){};
	Character(const sf::Texture &image, WorldManager *sb);
	virtual ~Character() ;

	sf::Texture texture;
	sf::Sprite sprite;
	virtual void update(float time, int offsetX, int offsetY)
	{	
		sprite.setPosition(X - offsetX, Y - offsetY);
	}	
};

class Beaver : public Character
{
	Beaver();
	void SetRandXY(int tryX, int tryY, const Map& MapW);
};

enum Direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
};

class Snake : public Character
{
public:
	Direction HeadDir = RIGHT;
	int HeadPositionX = 30;
	int HeadPositionY = 0;
	int Lenght = 1;
	

	std::vector<Section> sect;
	std::list<Section> PathToGo;
	
	Snake(){};
	Snake(sf::Texture, int tX, int tY, float SpawnT, WorldManager *sb);
	~Snake()override {};
	
	void ShiftSnake();
	void Move(Direction Dir);
	void RotateHead();
	void update(float time) override;
	void DrawSection(sf::RenderWindow *sf_win, bool Horisontal, bool first, int X, int Y);
	void draw(sf::RenderWindow *sf_win) override;
	void MoveAlongPath();
	void PrintPath();
	void Grow();
};

