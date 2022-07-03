#include <vector>
#include <memory>

namespace sf
{
	class RenderWindow;
	class Text;
	class Font;
	class Event;
}
class MenuManager
{
	std::vector<std::string> MenuItems;
	unsigned int Selected = 0;
	std::shared_ptr<sf::Font> p_myFont;
	std::shared_ptr<sf::Text> p_Text;	

public:
	MenuManager();
	
	int KeyboardEvent(sf::Event event);  // return Exit
	void Draw(sf::RenderWindow* Window);


};
