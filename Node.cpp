
#include "Node.h"
#include "AStar.h"



void Node::initDefNode(const int& x1, const int& y1)
{
	x = x1;
	y = y1;
	isWall = false;
	isVisited = false;
	parent = nullptr;
}

