#include <iostream>

#include "Engine.h"
#include <SFML/Graphics.hpp>
//-std=c++11
//-std=gnu++11
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main(int argc, char** argv)
{
	Engine Game;
	try
	{
		Game.Run();
	}
	catch(...)
	{
		std::cerr<< "Error";
	}
	
    return 0;
}
