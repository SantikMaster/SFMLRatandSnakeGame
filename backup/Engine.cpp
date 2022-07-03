#include <iostream>
#include <memory>
#include <list>
#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "Menu.h"
#include "WorldManager.h"


Engine::Engine()
{
	Window = std::make_shared<sf::RenderWindow>(sf::VideoMode(500, 500), "SFML works!");
	World = std::make_shared<WorldManager>();
	Menu = std::make_shared<MenuManager>();	
	
	sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    World.get()->push_back(shape);
    
    sf::CircleShape shape2(200.f);
    shape2.setFillColor(sf::Color::Red);
	World.get()->push_back(shape2);    

	sf::RectangleShape shape3(sf::Vector2f(120, 50));
	shape3.setPosition(100, 300);
    shape3.setFillColor(sf::Color::Blue);
	World.get()->push_back(shape3); 
	
	state = MENU_ST;
	
}
void Engine::HandleEvents()
{
	sf::Event event;
	int Result;
    while (Window.get()->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
                Window.get()->close();
        if(state == MENU_ST)
		{
			Result=Menu.get()->KeyboardEvent(event);
			if (Result==1)
			{
				state = GAME_ST;	
			}
			else if (Result==2) Window.get()->close();
		}
		if(state == GAME_ST)
		{
			if(event.key.code == sf::Keyboard::Escape)
			{
				state = MENU_ST;
			}
			else World.get()->KeyboardEvent(event);
			
			
		}
		
    }
}
void Engine::Run()
{    
    while (Window.get()->isOpen())
    {
        HandleEvents();
		Draw();	
    }
}
void Engine::Draw()
{
	switch (state)
	{
		case INIT_ST:
	
		break;	
		
		case MENU_ST:
			Menu.get()->Draw(Window.get());
		break;
		
		case GAME_ST:
			World.get()->Update();	
			World.get()->Draw(Window.get());		
		break;
	}

}
void Engine::Stop()
{
	
}
