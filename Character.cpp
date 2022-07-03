#include "Character.h"
#include "WorldManager.h"
#include "Map.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#undef __STRICT_ANSI__
#define M_PI 3.14159265358979323846
#include <cmath>
int	Character::Amount ;

void Character::update(float time)
{
//	std::cout<<"time "<<time<< "\n";
	sprite.setPosition(X - WorldManager::offsetX, Y - WorldManager::offsetY);
	X += dX*time*0.0001;
	Y += dY*time*0.0001;	

}
Character::~Character() 
{
	World->Detach(this);
}
Character::Character(const sf::Texture &image, WorldManager *sb)
{
	Amount++;
	Counter = Amount;
	sb->Attach(this); 
	World = sb;
		 
	sprite.setTexture(image);
	
	bool colresult = true;
	while (colresult)
	{	
		X = (rand()%Map::MapSize)*Map::TileSize;		// start position
		Y = (rand()%Map::MapSize)*Map::TileSize;
	    colresult =	World->WorldMap.Collide(X, Y, Map::TileSize, Map::TileSize);
	//	WorldManager::WorldMap.Collide(X, Y, Map::TileSize, Map::TileSize);
	//	 false;
	}
			// start position
	sprite.setTextureRect(sf::IntRect(0, 0, 1500 , 1500));
	sprite.scale(0.03f, 0.03f);
	sprite.setPosition(X, Y);
}
Beaver::Beaver()
{
 	Width = 100;
 	Height = 100;	
}
void Beaver::SetRandXY(int tryX, int tryY, const Map& WorldMap)
{
	do
	{
		X = std::rand()%tryX;
		Y =	std::rand()%tryY;	
	}while((WorldMap.Collide(X,Y, Width, Height))==true);	
}
Snake::Snake(sf::Texture Txtr, int tX, int tY, float SpawnT = 0, WorldManager *sb= nullptr)
{	
    World = sb;
	texture = Txtr;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 100 , 100 ));
	sprite.scale(sf::Vector2f(-0.35,0.35));
	
	SpawnTime = SpawnT;
	
	
	X = tX; Y = tY;
	//Txtr
	Section newSect;
	for(int i = 0; i< Lenght; i++)
	{
		newSect.X = X - i*Map::TileSize;;
		newSect.Y = Y;
		newSect.Horizontal = true;
		sect.push_back(newSect);
	}	
}
void Snake::Grow()
{
	Lenght++;
	Section newSect;

	newSect.X = sect.back().X - Map::TileSize;
	newSect.Y = sect.back().Y;
	newSect.Horizontal = true;
	sect.push_back(newSect);
		
}
void Snake::update(float time)
{	
	this->Character::update(time);
	//	std::cout<<time<< "\n";
	/**/
	if (IsPathAvaible)
	{
		MoveAlongPath();
	}
	
	if(((X-sect[0].X)<0 ))//&& !WorldManager::WorldMap.Collide(X, Y, Map::TileSize, Map::TileSize))
	{
		Move(LEFT);	
	}
	if(((X-sect[0].X)>Map::TileSize))// && !WorldManager::WorldMap.Collide(X, Y, Map::TileSize, Map::TileSize))
	{
		Move(RIGHT);		
	}
	if(((Y-sect[0].Y)<0)) //&& !WorldManager::WorldMap.Collide(X, Y, Map::TileSize, Map::TileSize))
	{
		Move(UP);		
	}
	else if(((Y-sect[0].Y)>Map::TileSize)) //&& !WorldManager::WorldMap.Collide(X, Y, Map::TileSize, Map::TileSize))
	{
		Move(DOWN);	
	}
	
}
void Snake::MoveAlongPath()
{
	if (PathToGo.empty() || PathToGo.back().Y == 0)
	{
		dX = 0;
		dY = 0;
		
//		std::cout<< "Empty";
	    return;
	}
		
	if (PathToGo.back().X>(int)(X/Map::TileSize))
	{
		dX = +1;
		dY = 0;
		
	}
	else if ((int)PathToGo.back().X<(int)(X/Map::TileSize))
	{
		dX = -1;
		dY = 0;
	}
	if ((int)PathToGo.back().Y>(int)(Y/Map::TileSize))
	{
		dX = 0;
		dY = +1;
	}	
	else if ((int)PathToGo.back().Y<(int)(Y/Map::TileSize))
	{
		dX = 0;
		dY = -1;
		
//			std::cout<< "Move path up"<< PathToGo.back().Y<<"   " << PathToGo.empty()<<  "  "<<"\n";
	}	/**/
	if (((int)PathToGo.back().Y*Map::TileSize == (int)Y)&&(PathToGo.back().X*Map::TileSize==(int)X))
	{
	//	std::cout << "Position Pr:" <<PathToGo.back().Y << "Y: "<<(int) Y <<  ":: "<< (PathToGo.back().X)<< "X: "<<(int)X <<"\n";
		dX = 0;
		dY = 0;
		PathToGo.pop_back();
	}
	
		
}
void Snake::PrintPath()
{
	for (auto it: PathToGo)
	{
//		std::cout << it.X << "  " << it.Y << " \n";
	}
}
void Snake::Move(Direction Dir)
{	
	HeadDir = Dir;
	RotateHead();
	
	World->CollideObjects(this);




	switch (Dir)
	{
		
		case RIGHT:
		{
			
			ShiftSnake();	
			sect[0].X+=Map::TileSize;
		}
		break;
		case LEFT:
		{
			ShiftSnake();	
			sect[0].X-=Map::TileSize;
		}
		break;	
		case DOWN:
		{
			ShiftSnake();	
			sect[0].Y+=Map::TileSize;
		}
		break;
		case UP:
		{
			ShiftSnake();	
			sect[0].Y-=Map::TileSize;
		}
		break;	
	};
	
	if(WorldManager::WorldMap.Collide(X, Y, Map::TileSize,Map::TileSize))
	{
		
		PathToGo.clear();
		X = sect[0].X;
	    Y = sect[0].Y;
		dX = 0;
		dY = 0;
	
		return;
			
	} 
	
}
void Snake::ShiftSnake()
{
//	std::cout<< "Shift\n";

	for (int i = sect.size()-1; i>0 ; i--)
	{
		sect[i]=sect[i-1];
	}	
}
void Snake::RotateHead()
{
	switch (HeadDir)
	{
		case UP:
		sprite.setPosition(sect[0].X-Map::TileSize, sect[0].Y);
		sprite.setRotation(-90.f);
		HeadPositionX = 0;
		HeadPositionY = 0;
		break;
		case DOWN:
		sprite.setPosition(sect[0].X, sect[0].Y+30);
		sprite.setRotation(90.f);
		HeadPositionX = Map::TileSize;
		HeadPositionY = Map::TileSize;
		break;
		case LEFT:
		sprite.setPosition(sect[0].X-60, sect[0].Y+30);
		sprite.setRotation(180.f);
		HeadPositionX = 0;
		HeadPositionY = Map::TileSize;
		break;
		case RIGHT:
		sprite.setPosition(sect[0].X, sect[0].Y);
		sprite.setRotation(0.f);
		HeadPositionX = Map::TileSize;
		HeadPositionY = 0;
		break;
					
	}	
}
void Character::draw(sf::RenderWindow *sf_win)
{
	sf_win->draw(sprite);
}
void Snake::draw(sf::RenderWindow *sf_win)
{

	for(int i = 1; i< sect.size(); i++)
	{

		DrawSection(sf_win, LEFT, false , sect[i].X, sect[i].Y);
	}
	DrawSection(sf_win, LEFT, true , sect[0].X, sect[0].Y);
	
	sf::CircleShape circle;
	circle.setRadius(5);
	circle.setOutlineColor(sf::Color::Red);
	circle.setPosition(X, Y);
	sf_win->draw(circle);

}
void Snake::DrawSection(sf::RenderWindow *sf_win, bool Horisontal, bool first, int X, int Y)
{
	using namespace sf;
	if(!first)
	{
		sf::RectangleShape Rect(sf::Vector2f(Map::TileSize, Map::TileSize));
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
		sprite.setPosition(X+HeadPositionX, Y+HeadPositionY);
		sf_win->draw(sprite);
	}

}


