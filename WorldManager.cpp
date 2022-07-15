#include <iostream>
#include <list>
#include <map>
#include "WorldManager.h"
#include "Map.h"
#include "Character.h"
#include "AStar.h"
#include "Node.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
int	WorldManager::offsetX ;
int	WorldManager::offsetY ;
Map WorldManager::WorldMap;

WorldManager::WorldManager(Engine* Engine)
{
	C_Engine = Engine;
	WorldManager::offsetX = 0;
	WorldManager::offsetY = 0;

	std::string myfontFileName="Arial.ttf";
	p_myFont = std::make_shared<sf::Font>();
	p_Text = std::make_shared<sf::Text>();
	auto text = p_Text.get();
	
    if (!p_myFont.get()->loadFromFile(myfontFileName))
        {
        std::cout << "Could not find the font " << myfontFileName << std::endl;
        }
        
   	text->setFont(*p_myFont.get());
    text->setCharacterSize(48);
    text->setColor(sf::Color::White);

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
    if(!t.loadFromFile(beaver_str))
    {
    	std::cerr << "Could not load beaver texture";
	}
    TextureMap.insert(std::make_pair("beaver" , t));
  /* */ 
	
	clock = std::make_shared<sf::Clock>();
	clock2 = std::make_shared<sf::Clock>();
	SnakeClock = std::make_shared<sf::Clock>();
	
	SpawnTime = clock2.get()->getElapsedTime().asSeconds();

	Star = std::make_shared<AStar>();
	Star.get()->CollumsX = Map::MapSize+10;
	Star.get()->CollumsY = Map::MapSize+10;
	Star.get()->Init();
	WorldMap = Map(TextureMap["map"]);	
	
	Restart();
   /* Snake_list.push_back(std::make_shared<Snake>(TextureMap["snake"], Map::TileSize*10, Map::TileSize*12, GetTimeSec(), this));
   
	Player = std::make_shared<Beaver>(TextureMap["beaver"],  this);

	Player->X = 150;
	Player->Y = 330; */


	
	
	Potato = std::make_shared<sf::Sprite>();
	PotatoFont = std::make_shared<sf::Sprite>();
	auto potato = Potato.get();
	auto font = PotatoFont.get();
	
	potato->setTexture(TextureMap["potato"]);
	potato->setTextureRect(sf::IntRect(0, 0, 300 , 230 ));
	potato->scale(0.5f, 0.5f);
	
	font->setTexture(TextureMap["font"]);
	font->setTextureRect(sf::IntRect(0, 0, 2000 , 2000 ));
	font->scale(0.5f, 0.5f);	
	

}
void WorldManager::Restart()
{
	Level = 1;
	Player.reset();
	Player = std::make_shared<Beaver>(TextureMap["beaver"],  this);
	
	Snake_list.clear();
	Snake_list.push_back(std::make_shared<Snake>(TextureMap["snake"], Map::TileSize*10, Map::TileSize*12, GetTimeSec(), this));
	Player->X = Map::TileSize*Map::Level1XStart;
	Player->Y = Map::TileSize*Map::Level1YStart;

	
	WorldMap.Initialize();
}
void WorldManager::Detach(Character* o)
{
	auto it = observers.begin();
	for( it = observers.begin();it!=observers.end();it++)
	{
		if (*it == o)
		{
			std::cout<< "REMOVED" << o->Counter << "\n";
			observers.erase(it);
		}
	}
	
}
float WorldManager::GetTimeSec()
{
	sf::Time elapsed1 = clock2.get()->getElapsedTime();
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
void WorldManager::StartLevel2()
{
	Player.reset();
	Player = std::make_shared<Beaver>(TextureMap["beaver"],  this);
	
	Snake_list.clear();
	Snake_list.push_back(std::make_shared<Snake>(TextureMap["snake"], Map::TileSize*10, Map::TileSize*12, GetTimeSec(), this));
	Player->X = Map::TileSize*5;
	Player->Y = Map::TileSize*11;

	WorldMap.LoadLevel2();
	C_Engine->state = Engine::PAUSE_ST;
}
void WorldManager::NextLevel()
{
	Level++;
	switch (Level)
	{
		case 2: StartLevel2(); break;
		case 3: C_Engine->state = Engine::WIN_ST; break;
	}
		
}
void WorldManager::CollideObjects(Character* player)
{
// --- potatoes colide
	int pX = player->X ;
	int pY = player->Y;
	Snake* sn = dynamic_cast<Snake*>(player);
	
	bool Detached = false;
	for (auto o = observers.begin(); o!=observers.end(); o++) 
	{
	
		Character *potato = dynamic_cast<Character*>(*o);
		if (potato)
		{
			Beaver* bv = dynamic_cast<Beaver*>(player);
			if(bv!=nullptr)
			{
				pX = player->X ;
				pY = player->Y;
				pX += Map::TileSize; 
				pY += Map::TileSize; 
			}
			    
			if ((pX>= potato->X)&&(pX<= potato ->X + Map::TileSize)
				&&(pY >= potato ->Y)&&(pY <=potato->Y + Map::TileSize)
				)
			{
						
		    	player->PickedPotato += 1;
				if(bv!=nullptr)
				{
					bv->Bomb++;
					if(bv->PickedPotato>=PotatoesToWin)
						NextLevel();
				//	C_Engine->state = Engine::WIN_ST;
				}
		
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
		
	}
	// -- beavers collide
	if(sn!=nullptr)
	{
		pX = player->X;
		pY = player->Y;
		int beaverX = Player.get()->X;
		int beaverY = Player.get()->Y;
		if ((pX/Map::TileSize == beaverX/Map::TileSize)&&(pY/Map::TileSize == beaverY/Map::TileSize)
//		(pX> beaverX - Map::TileSize)&&(pX< beaverX + Map::TileSize)&&(pY/Map::TileSize == beaverY/Map::TileSize)
//				&&(pY > beaverY- Map::TileSize)&&(pY <beaverY + Map::TileSize)
				)
			{			
			    sn->Grow(); 
			    std::cout<<"Rat die!!! \n";
			    C_Engine->state = Engine::LOSE_ST;
			    Player.get()->Die();
			}	
	}
		
}
void WorldManager::Draw(sf::RenderWindow* Window)
{
	Window->clear();
    

	DrawFont(Window, TextureMap["map"]);

	WorldMap.draw(Window);
	DrawScoreAndStoppers(Window);
	
	Player.get()->draw(Window);
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
void WorldManager::DrawScoreAndStoppers(sf::RenderWindow *sf_win)
{
	sf::RectangleShape rectangle(sf::Vector2f(18*Map::TileSize, 4*Map::TileSize));
	rectangle.setPosition(00,15*Map::TileSize);
	rectangle.setFillColor(sf::Color(50, 150, 40));
	
	sf_win->draw(rectangle);


	if (Player.get()!=nullptr)
	{
		p_Text.get()->setCharacterSize(36);
	
		std::string ScoreTxt;
		ScoreTxt = "Score: " + std::to_string(Player.get()->PickedPotato);
		p_Text.get()->setString(ScoreTxt);
		p_Text.get()->setPosition(50, 16*Map::TileSize);
		sf_win->draw(*p_Text.get());
		
		ScoreTxt = "Bomb: " + std::to_string(Player->Bomb);
		p_Text.get()->setString(ScoreTxt);
		p_Text.get()->setPosition(200, 16*Map::TileSize);
		sf_win->draw(*p_Text.get());
		
		ScoreTxt = "Level: " + std::to_string(Level);
		p_Text.get()->setString(ScoreTxt);
		p_Text.get()->setPosition(380, 16*Map::TileSize);
		sf_win->draw(*p_Text.get());
	}
	
}
void WorldManager::AI_Move(Character &AI, float time)
{

}
void WorldManager::DrawFont(sf::RenderWindow *sf_win, const sf::Texture &t)
{
	auto font = PotatoFont.get();
	int TreeX = 00, TreeY = 00;
	font->setPosition(TreeX - offsetX/5, TreeY-offsetY/5);
	sf_win->draw(*font);
	
	sf::RectangleShape rectangle(sf::Vector2f(18*Map::TileSize, 18*Map::TileSize));
	rectangle.setPosition(00,0);
	rectangle.setFillColor(sf::Color(00, 0, 0, 100));
	rectangle.setOutlineThickness(0.f);
	
	sf_win->draw(rectangle);

	
}
void WorldManager::SnakesGoToBeavers()
{
	for (auto o : Snake_list) 
    {
		auto sn = o.get();
      
        GoToNearestBeaver(sn);
   	}
	
}
void WorldManager::Update()
{
	float timeSec = clock2.get()->getElapsedTime().asSeconds();

    if((-SpawnTime+timeSec)>=SpawnPass)
    {
    	
		if(observers.size()<MaxPotatoes)
		{
			SpawnTime=clock2.get()->getElapsedTime().asSeconds();
       		Character_list.push_back(std::make_shared<Character>(TextureMap["potato"], this));	
		}  
   	}
   if(SnakeClock.get()->getElapsedTime().asSeconds()>=1)
   {
   //	    std::cout<< "tick\n";
    	SnakesGoToBeavers();
   	    SnakeClock->restart();  
   }
  
	Player.get()->update(GetTimeMicrosec());
	for (auto o : Snake_list) 
    {
		auto sn = o.get();
      
        sn->update(GetTimeMicrosec());
   
   	}
	clock.get()->restart();
}

void WorldManager::GoToNearestPotato(Snake *player) //* TO EDIT
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
		
		for(auto it = observers.begin();it!=observers.end();it++)
		{
		  Ch = *it;
			std::cout<< "Exist" << Ch->Counter << "\n";
	
		}
			
	}
	else
		GoToRandPotato(player);
	
}
void WorldManager::GoToNearestBeaver(Snake *snake) //* TO EDIT
{

	int X = Player.get()->X/Map::TileSize;
	int Y = Player.get()->Y/Map::TileSize;
	
	Star.get()->Init();	
	Star.get()->LoadMap(WorldMap);
	Star.get()->Start = &(Star.get()->Nodes[(int)(snake->Y)/Map::TileSize][(int)(snake->X)/Map::TileSize]);
	Star.get()->End = &(Star.get()->Nodes[Y][X]);
	

	Star.get()->AStarAlg();
		
	if (Star.get()->IsPathAvaible() )
	{
		Star.get()->SetPath(&(snake->PathToGo));
		snake->IsPathAvaible = true;				
	}
	else
		snake->IsPathAvaible = false;
	
}
void WorldManager::GoToRandPotato(Snake *player) //* TO EDIT
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


		int X = Ch->X/Map::TileSize;
		int Y = Ch->Y/Map::TileSize;
		Star.get()->Start = &(Star.get()->Nodes[(int)(player->Y)/Map::TileSize][(int)(player->X)/Map::TileSize]);
		Star.get()->End = &(Star.get()->Nodes[Y][X]);
	
		Star.get()->LoadMap(WorldMap);
		Star.get()->AStarAlg();
	
	}while(Star.get()->IsPathAvaible() != true && i++<5);
	if (Star.get()->IsPathAvaible())
	{
		
		Star.get()->SetPath(&(player->PathToGo));
		player->IsPathAvaible = true;	
		std::cout << "Go!!"<< Ch->X<< " "<< Ch->Y<<"\n";
		
			
	}
	else
	{
		player->IsPathAvaible = false;	
		std::cout << "No path!!\n";	
	}
	
}

bool WorldManager::GoToDestination(float goY, float goX, Snake *player) //* TO EDIT
{

	int X = goX/Map::TileSize;
	int Y = goY/Map::TileSize;
 
	Star.get()->Start = &(Star.get()->Nodes[(int)(player->Y)/Map::TileSize][(int)(player->X)/Map::TileSize]);
	Star.get()->End = &(Star.get()->Nodes[Y][X]);
	 
	Star.get()->LoadMap(WorldMap);
	Star.get()->AStarAlg();

	

	if (Star.get()->IsPathAvaible() )
	{
		
		Star.get()->SetPath(&(player->PathToGo));
		player->IsPathAvaible = true;	
		return true;
			
	}
	player->IsPathAvaible = false;	
 
	return false; 
	
}

void WorldManager::KeyboardEvent(sf::Event event,  sf::RenderWindow *sf_win)
{
	auto player = Player.get();


	if (event.type==sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
		case sf::Keyboard::W:
			if(player->dY>-1)player->dY -= 1;
			player->dX = 0;
		break;
		case sf::Keyboard::Down:
		case sf::Keyboard::S:
			if(player->dY<1)player->dY += 1;
			player->dX = 0;
		break;	
		case sf::Keyboard::Left:
		case sf::Keyboard::A:
			if(player->dX>-1)player->dX -= 1;
			player->dY = 0;
		break;	
		case sf::Keyboard::Right:
		case sf::Keyboard::D:
			if(player->dX<1)player->dX += 1;
			player->dY = 0;
		break;

		case sf::Keyboard::E:
			player->DigHole = true;
			player->DigHoleStartTime = GetTimeSec();
		break;
		
		case sf::Keyboard::Q:
			if(Player->Bomb>0)
			{
				WorldMap.BuildWall(player->X, player->Y, player->dX, player->dY);	
				Player->Bomb--;
			}
			
		break;
		};
	}	
}

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
