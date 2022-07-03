#include <SFML/Graphics.hpp>
#include <vector>

namespace sf
{
	class Time;
	class Texture;
}
class Character
{
public:
	float X = 0, Y = 0, dX = 0, dY = 0;
	int Width = 0;
	int Height = 0;
	bool OnGround = true;
	bool AI_LeftMove = false;
	
	virtual void update(float time);
	
	Character() {};
	virtual ~Character() = default;
	
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
	void SetRandXY(int tryX, int tryY);
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
	Direction Dir = RIGHT;
	int Lenght = 10;
	
	struct Section
	{
		int X, Y;
		bool Horizontal;
	};
	std::vector<Section> sect;
	
	Snake(){};
	Snake(sf::Texture, int tX, int tY);
	~Snake()override {};
	
	void ShiftSnake();
	void Move(Direction Dir);
	void update(float time) override;
	void DrawSection(sf::RenderWindow *sf_win, bool Horisontal, bool first, int X, int Y);
	void draw(sf::RenderWindow *sf_win);
};

