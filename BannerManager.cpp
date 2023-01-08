#include <iostream>

#include "BannerManager.h"
#include <SFML/Graphics.hpp>
BannerManager::BannerManager()
{
	std::string myfontFileName="../Arial.ttf";
	p_myFont = std::make_shared<sf::Font>();
	p_Text = std::make_shared<sf::Text>();
	auto text = p_Text.get();
	
    if (!p_myFont.get()->loadFromFile(myfontFileName))
        {
        std::cout << "Could not find the font " << myfontFileName << std::endl;
        }
        
   	text->setFont(*p_myFont.get());
    text->setCharacterSize(36);
    text->setColor(sf::Color::White);
}
void BannerManager::Draw(sf::RenderWindow* Window, State st)
{
		    Window->clear();
	sf::RectangleShape rectangle(sf::Vector2f(2000, 2000));
	rectangle.setPosition(00,0);
	rectangle.setFillColor(sf::Color(sf::Color::White));
	
	Window->draw(rectangle);
	switch (st)
	{
	    case(LOSE):
	    {
	         sf::Texture Texture;
  	        Texture.loadFromFile("../Textures/Lost.jpg");
     	    sf::Sprite sprite(Texture);
	        Window->draw(sprite);
	        Window->display();
	    }break;
	    case(WIN):
	    {
	        sf::Texture Texture;
  	        Texture.loadFromFile("../Textures/Win.jpg");
     	    sf::Sprite sprite(Texture);
	        Window->draw(sprite);
	        Window->display();	
	    }break;	
	    case(PAUSE):
	    {
	        sf::Texture Texture;
  	        Texture.loadFromFile("../Textures/NextLevel.jpg");
     	    sf::Sprite sprite(Texture);
	        Window->draw(sprite);
	        Window->display();	
	    }break;
	    case(DESC):
	    {
	    	Window->clear();
	       	std::string ScoreTxt;
		    ScoreTxt = "The goal is to collect 10 potatos";
		    p_Text.get()->setString(ScoreTxt);
		    p_Text.get()->setPosition(50, 50);
		    Window->draw(*p_Text.get());
		    ScoreTxt = "Avoid snakes";
		    p_Text.get()->setString(ScoreTxt);
		    p_Text.get()->setPosition(50, 100);
		    Window->draw(*p_Text.get());
		    ScoreTxt = "Shit out the potato to block the passage";
		    p_Text.get()->setString(ScoreTxt);
		    p_Text.get()->setPosition(50, 150);
		    Window->draw(*p_Text.get());
		    ScoreTxt = "You can dig new passages";
		    p_Text.get()->setString(ScoreTxt);
		    p_Text.get()->setPosition(50, 200);
		    Window->draw(*p_Text.get());
		    ScoreTxt = "Good luck!";
		    p_Text.get()->setString(ScoreTxt);
		    p_Text.get()->setPosition(50, 250);
		    Window->draw(*p_Text.get());
		    
		    ScoreTxt = "Kryvchikov Oleksii";
		    p_Text.get()->setString(ScoreTxt);
		    p_Text.get()->setPosition(100, 350);
		    Window->draw(*p_Text.get());
		    
	        Window->display();	
	    }break;
	    case(KEY):
	    {
	        Window->clear();
	       	std::string ScoreTxt;
		    ScoreTxt = "E - DIG (takes time)";
		    p_Text.get()->setString(ScoreTxt);
		    p_Text.get()->setPosition(50, 50);
		    Window->draw(*p_Text.get());
		    ScoreTxt = "Q - Block the passage(Shit)";
		    p_Text.get()->setString(ScoreTxt);
		    p_Text.get()->setPosition(50, 100);
		    Window->draw(*p_Text.get());

	        Window->display();	
	    }break;
	};
	
	
}
