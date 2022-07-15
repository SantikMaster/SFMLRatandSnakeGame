#include <memory>
namespace sf
{
	class RenderWindow;
	class Text;
	class Font;
}
class BannerManager
{
	std::shared_ptr<sf::Font> p_myFont;
	std::shared_ptr<sf::Text> p_Text;
public:
	enum State
	{
		LOSE,
		WIN,
		PAUSE,
		DESC,
		KEY,
	};
	BannerManager();
	void Draw(sf::RenderWindow* Window, State st);
};
