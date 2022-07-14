#include <iostream>

#include "BannerManager.h"
#include <SFML/Graphics.hpp>
BannerManager::BannerManager()
{
	
}
void BannerManager::Draw(sf::RenderWindow* Window, bool Lose)
{
	auto font = PotatoFont.get();
	int TreeX = 00, TreeY = 00;
	font->setPosition(TreeX - offsetX/5, TreeY-offsetY/5);
	sf_win->draw(*font);
}
