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
	int Lenght = 3;
	float Speed = 0.95;

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

class Beaver : public Character
{
	bool Alive = true;
public:
	float CurrentFrame = 0;
	float deltaFrame = 0.00001;
	int FramesX = 3; 
	int DigingTime = 1.5;
	bool DigHole = false;
	float DigHoleStartTime;
	int Bomb = 5;
	
	Beaver();
	Beaver(const sf::Texture &image, WorldManager *sb);
	bool FreeTilesInFront(int X, int Y, float dX, float dY, int& XTile, int& YTile);

	void SetRandXY(int tryX, int tryY, const Map& MapW);
	void draw(sf::RenderWindow *sf_win) override;
	void update(float time) override;
	void Die();
};


