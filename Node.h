#include <vector>
class Node
{

public:
	bool isWall = false;			
	bool isVisited = false;			
	float FCost;				
	float HCost;				
	int x;							
	int y;
	std::vector<Node*> Neighbours;
	Node* parent;					

	void initDefNode(const int& x1, const int& y1);	
};
