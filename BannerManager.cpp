#include <iostream>

#include "BannerManager.h"
#include <SFML/Graphics.hpp>
BannerManager::BannerManager()
{

  
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

//		std::cout << "draw die!!\n";
	         sf::Texture Texture;
  	        Texture.loadFromFile("Textures/Lost.jpg");
     	    sf::Sprite sprite(Texture);
	        Window->draw(sprite);
	        Window->display();
	    }break;
	    case(WIN):
	    {
	        sf::Texture Texture;
  	        Texture.loadFromFile("Textures/Win.jpg");
     	    sf::Sprite sprite(Texture);
	        Window->draw(sprite);
	        Window->display();	
	    }	
	    case(PAUSE):
	    {
	        sf::Texture Texture;
  	        Texture.loadFromFile("Textures/NextLevel.jpg");
     	    sf::Sprite sprite(Texture);
	        Window->draw(sprite);
	        Window->display();	
	    }break;
	};
	
	
}
