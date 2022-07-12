#include <SFML/Graphics.hpp>

class Map
{
	sf::Texture texture;
	sf::Sprite sprite;
public:
	static const int MapSize = 16;
	static const int TileSize = 30;
	
	std::string Tiles[ MapSize];
	Map(sf::Texture);
	Map() = default;
	
	void BuildWall(int X, int Y, float dX, float dY);
	void EraseWall(int X, int Y);
	draw(sf::RenderWindow *sf_win);
	bool Collide(int X, int Y, int Width, int Height) const;


	
	std::string Level[MapSize] = 
	 {

       "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
 
       "0   P    P      00            00                                             0                                                                           0",

       "0   PPP  P      00            00                                            0           w                                                               0",

       "0   PPPPPP     P00PPP         0                         P                   0 w                                                                         0",

       "0 P          P  00            0      PP                                     0     kk                                                                    0",

       "0PPPPP   P  PPP 0P            0                                             0    k  k    k    k                                                         0",

       "0  P     P      0      P      0               PPP                          0    k      kkk  kkk  w                                                     0",

       "0 PPPP  P       0             0                P                           r0    k       k    k                                                         0",

       "0 P  P  PPP     0             0             P                            rr0    k  k                                                                   0",

       "0    P          0             0                              OOO        rrr0     kk                                                                    0",

       "0PPP P       PPP0   PPPPP     0                                        rrrr0                                                                           0",

       "0  P    PPP     0             0       0t0                             rrrrr0                                                                           0",

       "0P P            0             0        000         PPP               rrrrrr0           G                                                               0",

       "0               0             0        000              000         rrrrrrr0                                                                           0",

       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000PPPPPPPPPPPP"
	}; 
};
