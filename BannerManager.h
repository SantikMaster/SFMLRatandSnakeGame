namespace sf
{
	class RenderWindow;

}
class BannerManager
{
	
public:
	enum State
	{
		LOSE,
		WIN,
		PAUSE,
	};
	BannerManager();
	void Draw(sf::RenderWindow* Window, State st);
};
