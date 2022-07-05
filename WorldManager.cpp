#include <iostream>
#include <list>
#include <map>
#include "WorldManager.h"
#include "Map.h"
#include "Character.h"
#include "AStar.h"
#include "Node.h"
#include <SFML/Graphics.hpp>
int	WorldManager::offsetX ;
int	WorldManager::offsetY ;
Map WorldManager::WorldMap;

WorldManager::WorldManager()
{
	WorldManager::offsetX = 0;
	WorldManager::offsetY = 0;
	
//	Character::Amount = 0;

	sf::Texture t;
    if(!t.loadFromFile(map_str))
    {
    	std::cerr << "Could not load map texture";
	}
    TextureMap.insert(std::make_pair("map" , t));
    if(!t.loadFromFile(snake_str))
    {
    	std::cerr << "Could not load snake texture";
	}
    TextureMap.insert(std::make_pair("snake" , t));
    if(!t.loadFromFile(potato_str))
    {
    	std::cerr << "Could not load potato texture";
	}
    TextureMap.insert(std::make_pair("potato" , t));
    if(!t.loadFromFile(potatoFont_str))
    {
    	std::cerr << "Could not load font texture";
	}
    TextureMap.insert(std::make_pair("font" , t));
    
    
	
	clock = std::make_shared<sf::Clock>();
	clock2 = std::make_shared<sf::Clock>();
	
	SpawnTime = clock2.get()->getElapsedTime().asSeconds();

	Star = std::make_shared<AStar>();
	Star.get()->CollumsX = Map::MapSize+10;
	Star.get()->CollumsY = Map::MapSize+10;
	Star.get()->Init();
	
//		std::cout << "log1";
    Snake_list.push_back(std::make_shared<Snake>(TextureMap["snake"], Map::TileSize*10, Map::TileSize*12, GetTimeSec(), this));
   
	Player = std::make_shared<Snake>(TextureMap["snake"], Map::TileSize*10, Map::TileSize*3, GetTimeSec(), this);
//	I_Snake = std::make_shared<Snake>(TextureMap["snake"], Map::TileSize*10, Map::TileSize*12, GetTimeSec(), this);
//			std::cout << "log2";
//	WorldMap = std::make_shared<Map>(TextureMap["map"]);
	WorldMap = Map(TextureMap["map"]);
	
	
	Potato = std::make_shared<sf::Sprite>();
	PotatoFont = std::make_shared<sf::Sprite>();
	auto potato = Potato.get();
	auto font = PotatoFont.get();
	
	potato->setTexture(TextureMap["potato"]);
	potato->setTextureRect(sf::IntRect(0, 0, 300 , 230 ));
	potato->scale(0.5f, 0.5f);
	
	font->setTexture(TextureMap["font"]);
	font->setTextureRect(sf::IntRect(0, 0, 600 , 600 ));
	font->scale(0.5f, 0.5f);	
	
//	std::shared_ptr<Character> potato_ch;
//	potato_ch = std::make_shared<Character>(TextureMap["potato"], this);
//	Character_list.push_back(std::make_shared<Character>(TextureMap["potato"], this));
}
void WorldManager::Detach(Character* o)
{
//	auto it =observers.begin();
	auto it = observers.begin();
	for( it = observers.begin();it!=observers.end();it++)
	{
//		std::cout << "Exists: " << *(*it)->Counter <<"\n";
		if (*it == o)
		{
			std::cout<< "REMOVED" << o->Counter << "\n";
			observers.erase(it);
		}
	}
	
}
float WorldManager::GetTimeSec()
{
	sf::Time elapsed1 = clock.get()->getElapsedTime();
	return elapsed1.asSeconds() ;
}
int WorldManager::GetTimeMicrosec()
{
	sf::Time elapsed1 = clock.get()->getElapsedTime();
	return elapsed1.asMicroseconds();
}

template <class T>
	void WorldManager::push_back(T& Object)
{
	std::cout <<"Not added\n";
}
void WorldManager::push_back(int Object)
{
	std::cout <<"added int\n";
}
void WorldManager::push_back(sf::CircleShape &Obj)
{
	std::cout <<"added Circle\n";

}
void WorldManager::push_back(sf::RectangleShape &Obj)
{
	std::cout <<"added Rectangle\n";

}
void WorldManager::CollideObjects(Character* player)
{
//	auto player = Player.get();
	bool Detached = false;
	for (auto o = observers.begin(); o!=observers.end(); o++) 
	{
	
		Character *potato = dynamic_cast<Character*>(*o);
		if (potato)
		{
			if ((player->X > potato->X)&&(player->X <= potato ->X + Map::TileSize)
				&&(player->Y > potato ->Y)&&(player->Y <=potato->Y + Map::TileSize)
				)
			{
						
				player->PickedPotato += 1;
				Snake* sn = dynamic_cast<Snake*>(player);
		
	        	if(sn!=nullptr)
			    	sn->Grow();
			    	
				Detach(potato);
		//		GoToNearestLocation();
		//		std::cout<< " log 111\n";
				Detached = true;
			}
		}
	}
	if(Detached)
	{
		Snake* sn = dynamic_cast<Snake*>(player);
		
		if(sn!=nullptr)
	    	GoToNearestLocation(sn);
	}
		
}
void WorldManager::Draw(sf::RenderWindow* Window)
{
	Window->clear();

	DrawFont(Window, TextureMap["map"]);

	WorldMap.draw(Window);
	Player.get()->draw(Window);
//	I_Snake.get()->draw(Window);
	for (auto o : Snake_list) 
	{
		auto sn = o.get();
        sn->draw(Window);
   	}

 	for (auto* o : observers) 
	{
      o->draw(Window);
   	}


    Window->display();
    
    
}
void WorldManager::AI_Move(Character &AI, float time)
{
/*	bool OnGrTemp = AI.OnGround;
	int tempX = AI.X;
	int tempY = AI.Y;
	if(AI.AI_LeftMove == true)
	{
		AI.dX = Velocity/2;
	}
	else AI.dX = -Velocity/2;
	
	
	AI.update(time);
	if( OnGrTemp != AI.OnGround )
	{
		AI.dY = -Velocity*(1-std::rand()%3);
		AI.dX = -2*Velocity*(1-std::rand()%3);
		AI.AI_LeftMove = ( std::rand()%2);
		AI.OnGround = false;
		AI.update(time);
	}
	if(AI.X == tempX)
	{
		AI.dY = -Velocity*(1-std::rand()%3);
		AI.AI_LeftMove = ( std::rand()%2);
		AI.OnGround = false;
		AI.update(time);
	}*/
}
void WorldManager::DrawFont(sf::RenderWindow *sf_win, const sf::Texture &t)
{
	auto font = PotatoFont.get();
	int TreeX = 100, TreeY = 130;
	font->setPosition(TreeX - offsetX/5, TreeY-offsetY/5);
	sf_win->draw(*font);
	
}
void WorldManager::Update()
{
	float timeSec = clock2.get()->getElapsedTime().asSeconds();

    if(-SpawnTime+timeSec>=SpawnPass)
    {
    //    std::cout<<"Spawned potato!!\n";
        SpawnTime=clock2.get()->getElapsedTime().asSeconds();
        Character_list.push_back(std::make_shared<Character>(TextureMap["potato"], this));
        
        GoToNearestLocation(Player.get());
        
        for (auto o : Snake_list) 
    	{
		     auto sn = o.get();
      
            GoToNearestLocation(sn);
   	    }
      
	}


        

    
	Player.get()->update(GetTimeMicrosec());
	for (auto o : Snake_list) 
    {
		auto sn = o.get();
      
        sn->update(GetTimeMicrosec());
   
   	}
	clock.get()->restart();
}

void WorldManager::GoToNearestLocation(Snake *player) //* TO EDIT
{
	

	
	if(observers.empty())
	{	
//		std::cout<<"No potatoes\n";
		return;
	}
	auto it = *std::min_element(observers.begin(), observers.end(), [&player](Character * a, Character * b) 
		{
            int Xr = a->X - player->X;
            int Yr = a->Y - player->Y;
            
            int Xu = b->X - player->X;
            int Yu = b->Y - player->Y;
            
      		return (Xr*Xr + Yr*Yr) < (Xu*Xu + Yu*Yu);
		});
		
	int X = it->X/Map::TileSize;
	int Y = it->Y/Map::TileSize;
	Star.get()->Start = &(Star.get()->Nodes[(int)(player->Y)/Map::TileSize][(int)(player->X)/Map::TileSize]);
	Star.get()->End = &(Star.get()->Nodes[Y][X]);
	
	Star.get()->LoadMap(WorldMap);
	Star.get()->AStarAlg();
		
	if (Star.get()->IsPathAvaible() )
	{
		
		auto Ch = it;
		Star.get()->SetPath(&(player->PathToGo));
		player->IsPathAvaible = true;	
//		std::cout << "Go Near"<< Ch->X<< " "<< Ch->Y<<"\n";
	//	Player.get()->TestFlag = true;
		
		for(auto it = observers.begin();it!=observers.end();it++)
		{
//		std::cout << "Exists: " << *(*it)->Counter <<"\n";
		  Ch = *it;
			std::cout<< "Exist" << Ch->Counter << "\n";
	
		}
			
	}
	else
		GoToRandLocation(player);
	
}
void WorldManager::GoToRandLocation(Snake *player) //* TO EDIT
{

	int i = 0;
	auto it = observers.begin();
	for( it = observers.begin();it!=observers.end();it++)
	{
		auto Ch = *it;
		std::cout << "Exists: " << Ch->Counter <<"\n";
	}
	auto Ch = *it;
    do
    {
    	it = observers.begin();	
		int Size = observers.size();
		if (Size!=0)
			std::advance (it,std::rand()%Size);
		Ch = *it;	


//			auto player = Player.get();
		int X = Ch->X/Map::TileSize;
		int Y = Ch->Y/Map::TileSize;
		Star.get()->Start = &(Star.get()->Nodes[(int)(player->Y)/Map::TileSize][(int)(player->X)/Map::TileSize]);
		Star.get()->End = &(Star.get()->Nodes[Y][X]);
	
		Star.get()->LoadMap(WorldMap);
		Star.get()->AStarAlg();
	
	}while(Star.get()->IsPathAvaible() != true && i++<5);
	if (Star.get()->IsPathAvaible() )
	{
		
		Star.get()->SetPath(&(player->PathToGo));
		player->IsPathAvaible = true;	
		std::cout << "Go!!"<< Ch->X<< " "<< Ch->Y<<"\n";
	//	Player.get()->TestFlag = true;
		
		for(auto it = observers.begin();it!=observers.end();it++)
		{
//		std::cout << "Exists: " << *(*it)->Counter <<"\n";
		  Ch = *it;
			std::cout<< "Exist" << Ch->Counter << "\n";
	
		}
			
	}
	else
	{
		player->IsPathAvaible = false;	
		std::cout << "No path!!\n";	
	}
	
}

bool WorldManager::GoToDestination(float goY, float goX, Snake *player) //* TO EDIT
{
//	auto player = Player.get();
	
	int X = goX/Map::TileSize;
	int Y = goY/Map::TileSize;
//		std::cout << "log go 1";
	Star.get()->Start = &(Star.get()->Nodes[(int)(player->Y)/Map::TileSize][(int)(player->X)/Map::TileSize]);
	Star.get()->End = &(Star.get()->Nodes[Y][X]);
	
//		std::cout << "log go2";
	Star.get()->LoadMap(WorldMap);
	Star.get()->AStarAlg();
	
//	std::cout << "log go";
	
//	std::cout <<"Click:" <<position.x/Map::TileSize<< " " << position.y/Map::TileSize << "  \n"; 
	

	

	if (Star.get()->IsPathAvaible() )
	{
		
		Star.get()->SetPath(&(player->PathToGo));
		player->IsPathAvaible = true;	
		return true;
			
	}
	player->IsPathAvaible = false;	
//	std::cout << "No path!!\n";
	return false; 
	
}

void WorldManager::KeyboardEvent(sf::Event event,  sf::RenderWindow *sf_win)
{
	auto player = Player.get();
	if (event.type==sf::Event::MouseButtonPressed)
	{
		sf::Vector2i position = sf::Mouse::getPosition(*sf_win);
		GoToDestination(position.y, position.x, player);
	

	}
	if (event.type!=sf::Event::KeyPressed) return ;


	
	switch (event.key.code)
	{
		case sf::Keyboard::Up:
		case sf::Keyboard::W:
			player->dY -= 1;
			player->dX = 0;
		break;
		case sf::Keyboard::Down:
		case sf::Keyboard::S:
			player->dY += 1;
			player->dX = 0;
		break;	
		case sf::Keyboard::Left:
		case sf::Keyboard::A:
			player->dX -= 1;
			player->dY = 0;
		break;	
		case sf::Keyboard::Right:
		case sf::Keyboard::D:
			player->dX += 1;
			player->dY = 0;
		break;
	

	};
}

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
