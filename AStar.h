#include <vector>
#include <list>

struct Section;
class Node;
class Map;
class  AStar
{

public:	
	AStar();
	bool diagonal = false;
    int CollumsY ;
    int CollumsX ;
	
	std::vector<Node*> Nodes;
	Node* Start;
	Node* End;

	void Init();
	void initNeighBours();
	void AStarAlg();
	void LoadMap(const Map& WorldMap);	
	bool IsPathAvaible();

	
	void SetPath(std::list<Section> *Path);
};
