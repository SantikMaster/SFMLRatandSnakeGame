#include <iostream>

#include "Map.h"
#include "WorldManager.h"


Map::Map(sf::Texture Txtr)
{
	texture = Txtr;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 100 , 100 ));

}
void Map::Initialize()
{
	for (int i = 0; i < MapSize; i++)
	{
		Tiles[i] = Level[i];
	}	
}
void Map::LoadLevel2()
{
	for (int i = 0; i < MapSize; i++)
	{
		Tiles[i] = Level2[i];
	}
}
void Map::LoadLevel3()
{
	for (int i = 0; i < MapSize; i++)
	{
		Tiles[i] = Level3[i];
	}
}

void Map::draw(sf::RenderWindow *sf_win)
{
	sf::Sprite s;
    s.setTexture(texture);
	s.setTextureRect(sf::IntRect(230, 960, 60 , 60 ));
	s.scale(0.5f*TileSize/30, 0.5f*TileSize/30);

	for (int i = 0; i < MapSize; i++)
	{
		for (int j = 0; j < Tiles[i].length(); j++)
		{
			if(Tiles[i][j] == ' ')
			{
				continue;	
			}	
			else if(Tiles[i][j] == '0')
			{
	//			rectangle.setFillColor(sf::Color::Red);	
				s.setTextureRect(sf::IntRect(310, 980, 60 , 60 ));
			}
			else if(Tiles[i][j] == 'P')
			{
				//rectangle.setFillColor(sf::Color::Blue);	
				s.setTextureRect(sf::IntRect(260, 910, 60 , 60 ));
			}
			else if(Tiles[i][j] == 'r')
			{
				s.setTextureRect(sf::IntRect(310, 980, 60 , 60 ));
				//rectangle.setFillColor(sf::Color::Green);	
			}
			else if(Tiles[i][j] == 'w')
			{
				s.setTextureRect(sf::IntRect(330, 940, 60 , 60 ));	
				//rectangle.setFillColor(sf::Color::Yellow);	
			}
			          
			s.setPosition(j*TileSize - WorldManager::offsetX, i*TileSize - WorldManager::offsetY);
			sf_win->draw(s);
		}
	}
}	// */
void Map::BuildWall(int X, int Y, float dX, float dY)
{
	if (dX>0)
		Tiles[(int)Y/TileSize][(int)X/TileSize-1] = 'r';
	if (dY>0)
		Tiles[(int)Y/TileSize-1][(int)X/TileSize] = 'r';
	if (dX<0)
	{
		if (X%TileSize<5)
			Tiles[(int)Y/TileSize][(int)X/TileSize+1] = 'r';
		else Tiles[(int)Y/TileSize][(int)X/TileSize+2] = 'r';
	}
		
	if (dY<0)
	{
		if (Y%TileSize<5)
			Tiles[(int)Y/TileSize+1][(int)X/TileSize] = 'r';
		else Tiles[(int)Y/TileSize+2][(int)X/TileSize] = 'r';
	}				
}
void Map::EraseWall(int X, int Y)
{
	if(	Tiles[(int)Y/TileSize][(int)X/TileSize] != '0') Tiles[(int)Y/TileSize][(int)X/TileSize] = ' ';
}
bool Map::Collide(int X, int Y, int Width, int Height) const
{
	// метод должен карте принадлежать
	//Если с картой не сталкивается то false
	int Xst = X/TileSize;
	int Yst = Y/TileSize;
	int Xfin = Xst + Width/TileSize;
    int Yfin = Yst + Height/TileSize;
	

 //   Tiles[0].length()
    if (Xfin>Tiles[0].length()){Xfin=Tiles[0].length();}
    if (Yfin>MapSize){Yfin=MapSize;}
    
	for (int i = Xst; i < Xfin; i++)
	{
		for (int j = Yst; j < Yfin; j++)
		{
			if(Tiles[j][i] != ' ')
			{
				return true;	
			}
		}
	}	
	
	return false;
}
	

