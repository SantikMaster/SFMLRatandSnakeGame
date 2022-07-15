#include <iostream>

#include "Menu.h"
#include <SFML/Graphics.hpp>

MenuManager::MenuManager()
{
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
	
	MenuItems.push_back("Start/Resume");
	MenuItems.push_back("Restart");
	MenuItems.push_back("Keyboards");
	MenuItems.push_back("Description");	
	MenuItems.push_back("Exit");
	MenuItems.shrink_to_fit();
}
int MenuManager::KeyboardEvent(sf::Event event)
{
	if (event.type!=sf::Event::KeyPressed) return 0;
	std::cout<< "Menu Event\n";
	
	switch (event.key.code)
	{
		case sf::Keyboard::Up:
		case sf::Keyboard::W:
			if(Selected!=0)
			{
				Selected--;
			}

		break;
		case sf::Keyboard::Down:
		case sf::Keyboard::S:
			if(Selected<MenuItems.size()-1)
			{
				Selected++;
			}
		break;
		case sf::Keyboard::Return:
			if (Selected == 0) 
			{  // Game Start on First field
				return 1;
			}
			if (Selected == 1) 
			{  // Game Start on First field
				return 2;
			}
			if (Selected == 2) 
			{  // Game Start on First field
				return 3;
			}
			if (Selected == 3) 
			{  // Game Start on First field
				return 4;
			}
			if (Selected == MenuItems.size()-1)
			{// Game End on Last Field
				return 5;	
			}
		break;
		
	}
		
}
void MenuManager::Draw(sf::RenderWindow* Window)
{
//	std::cout<< "Menu Draw\n";
    Window->clear();
    unsigned int i = 0;
    
	for (auto it: MenuItems)
	{
	
		if (i==Selected)
		{
			p_Text.get()->setCharacterSize(48);
		}
		else 
		{
			p_Text.get()->setCharacterSize(36);
		}
		p_Text.get()->setString(it);
		p_Text.get()->setPosition(100, 100+i*60);
		Window->draw(*p_Text.get());
		i++;
	}

    Window->display();
}

