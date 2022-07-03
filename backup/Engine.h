#include<memory> 
#include <list>
namespace sf
{
	class RenderWindow;
	class CircleShape;
//	class RectangleShape;
}
class WorldManager;
class MenuManager;

	
class Engine
{
	enum State
	{	
		INIT_ST,
		MENU_ST,
		GAME_ST,
	};

	
public:
	State state = INIT_ST;
	void Run();
	void Stop();
	
	void Draw();
	void HandleEvents();
	Engine();
	
	std::shared_ptr<WorldManager> World;
	std::shared_ptr<MenuManager> Menu;
	std::list<sf::CircleShape> ObjList;
	std::shared_ptr<sf::RenderWindow> Window;	
};
