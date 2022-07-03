#include "Character.h"
#include "WorldManager.h"
#include <SFML/Graphics.hpp>

#undef __STRICT_ANSI__
#define M_PI 3.14159265358979323846
#include <cmath>

bool Collide(int X, int Y, int Width, int Height)
{
	// метод должен карте принадлежать
	//Если с картой не сталкивается то false
	return false;
}

void Character::update(float time)
{
	sprite.setPosition(X - WorldManager::offsetX, Y - WorldManager::offsetY);	
}
Beaver::Beaver()
{
 	Width = 100;
 	Height = 100;	
}
void Beaver::SetRandXY(int tryX, int tryY)
{
	do
	{
		X = std::rand()%tryX;
		Y =	std::rand()%tryY;	
	}while(Collide(X,Y, Width, Height)==true);	
}
Snake::Snake(sf::Texture Txtr, int tX, int tY)
{	
	texture = Txtr;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 100 , 100 ));
	sprite.scale(sf::Vector2f(-0.35,0.35));
	
	X = tX; Y = tY;
	//Txtr
	Section newSect;
	for(int i = 0; i< Lenght; i++)
	{
		newSect.X = X - i*30;
		newSect.Y = Y;
		newSect.Horizontal = true;
		sect.push_back(newSect);
	}

	
}

void Snake::update(float time)
{	
	Character::update(time, 0 , 0);
	if(abs(X-sect[0].X)<30)
	{
		Move(LEFT);
	}
	if(abs(X-sect[0].X)>30)
	{
		Move(RIGHT);
	}
	
}
void Snake::Move(Direction Dir)
{	

	switch (Dir)
	{
		case RIGHT:
		{
			ShiftSnake();	
			sect[0].X+=30;
		}
		break;
		case LEFT:
		{
			ShiftSnake();	
			sect[0].X-=30;
		}
		break;	
	};
	
}
void Snake::ShiftSnake()
{
	for (int i = 1; i< sect.size(); i++)
	{
		sect[i]=sect[i-1];
	}	
}
void Snake::draw(sf::RenderWindow *sf_win)
{
	DrawSection(sf_win, LEFT, true , sect[0].X, sect[0].Y);
	for(int i = 1; i< sect.size(); i++)
	{
		DrawSection(sf_win, LEFT, false , sect[i].X, sect[i].Y);
	}



}
void Snake::DrawSection(sf::RenderWindow *sf_win, bool Horisontal, bool first, int X, int Y)
{
	using namespace sf;
	if(!first)
	{
		sf::RectangleShape Rect(sf::Vector2f(30, 30));
		Rect.setFillColor(Color(200,200,70));
		Rect.setPosition(X, Y);
	
		sf::VertexArray lines(sf::LinesStrip, 2);
		sf_win->draw(Rect);
		
		int y2;
		
		for(int i = 0; i < 30; i++)
		{
			lines[0].position = sf::Vector2f(X+i, Y);
 			lines[0].color = Color(100,150,50);
 			if (i<=15)
			{
 				y2 = 7*sqrt(i);	
			}
 			else 
 				y2 = 7*sqrt(30-i);
 			lines[1].position = sf::Vector2f(X+i, Y+y2);
			lines[1].color =  Color(150,200,100);
			sf_win->draw(lines);
		}
	}
	else
	{
		sprite.setPosition(X+30, Y);
		sf_win->draw(sprite);
	}

}


