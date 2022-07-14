#include <iostream>

#include "BannerManager.h"
#include <SFML/Graphics.hpp>
BannerManager::BannerManager()
{

  
}
void BannerManager::Draw(sf::RenderWindow* Window, bool Lose)
{
		    Window->clear();
	sf::RectangleShape rectangle(sf::Vector2f(2000, 2000));
	rectangle.setPosition(00,0);
	rectangle.setFillColor(sf::Color(sf::Color::White));
	
	Window->draw(rectangle);
	if(Lose)
	{

//		std::cout << "draw die!!\n";
	    sf::Texture Texture;
  	    Texture.loadFromFile("Textures/Lost.jpg");
     	sf::Sprite sprite(Texture);
	    Window->draw(sprite);
	    Window->display();
	}
	else
	{
	
	    sf::Texture Texture;
  	    Texture.loadFromFile("Textures/Win.jpg");
     	sf::Sprite sprite(Texture);
	    Window->draw(sprite);
	    Window->display();	
	}
	
}
