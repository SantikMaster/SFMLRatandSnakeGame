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
	
	draw(sf::RenderWindow *sf_win);
	bool Collide(int X, int Y, int Width, int Height) const;


	
	std::string Level[MapSize] = 
	 {

       "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
 
       "0   P    P                                                                 0                                                                           0",

       "0   PPP  P                                                                 0           w                                                               0",

       "0   PPPPPP     PPPPPP                                  P                   0 w                                                                         0",

       "0 P          P                      PP                                     0     kk                                                                    0",

       "0PPPPP   P  PPP  P                                                         0    k  k    k    k                                                         0",

       "0  P     P             P                      PPP                          0    k      kkk  kkk  w                                                     0",

       "0 PPPP  P                                      P                           r0    k       k    k                                                         0",

       "0 P  P  PPP                                 P                            rr0    k  k                                                                   0",

       "0    P                                                       OOO        rrr0     kk                                                                    0",

       "0PPP P       PPP    PPPPP                                              rrrr0                                                                           0",

       "0  P    PPP                           0t0                             rrrrr0                                                                           0",

       "0P P                                   000         PPP               rrrrrr0           G                                                               0",

       "0                                      000              000         rrrrrrr0                                                                           0",

       "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP"
	}; 
};
