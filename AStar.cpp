#include "AStar.h"
#include "Node.h"
#include "Map.h"
#include<SFML/Graphics.hpp>
#include <iostream>
struct Section
{
		int X, Y;
		bool Horizontal = false;
};
AStar::AStar()
{	
	CollumsX = 10;
	CollumsY  = 10;

	Init();
}
void AStar::Init()
{
	Nodes.clear();
	for (int y = 0; y < CollumsY; y++)
	{
		Nodes.push_back(new Node[CollumsX]);
		for (int x = 0; x < CollumsX; x++)
		{
			Nodes[y][x].initDefNode( x, y);
		}
	}
	initNeighBours();
	Start = &Nodes[0][0];
	End = &Nodes[CollumsY - 1][CollumsX - 1];
}
bool AStar::IsPathAvaible()
{
	if (End->parent == nullptr) 
		return false;
		
	return true;
}

void AStar::SetPath(std::list<Section> *Path)
{
	Path->clear();

	if (End != nullptr)
	{
		Section Sect;
		Sect.X = End->x;
		Sect.Y = End->y;
	
		Path->push_back(Sect);
		Node* p = End->parent;
		if (p == nullptr) 
		{
			std::cerr<< "no path\n";
			return;	
		}
		Sect.X = p->x;
		Sect.Y = p->y;
		Path->push_back(Sect);
	
		while (p != nullptr && p != Start)
		{
			
			p = p->parent;
			Sect.X = p->x;
			Sect.Y = p->y;
			Path->push_back(Sect);
		}
			
	}
}
void AStar::LoadMap(const Map& WorldMap)
{
	for (int y = 0; y < CollumsY; y++)
	{
		for (int x = 0; x < CollumsX; x++)
		{
//			Star.Nodes[y][x].isWall = !Star.Nodes[y][x].isWall;
			if(WorldMap.Tiles[y][x]!=' ') Nodes[y][x].isWall = true;
		}
	
	}

}
void AStar::initNeighBours()
{
	for (int y = 0; y < CollumsY; y++)
	{
		for (int x = 0; x < CollumsX; x++)
		{
			if (x > 0) Nodes[y][x].Neighbours.push_back(&Nodes[y][x - 1]);
			if (y > 0) Nodes[y][x].Neighbours.push_back(&Nodes[y - 1][x]);
			if (x < AStar::CollumsX - 1) Nodes[y][x].Neighbours.push_back(&Nodes[y][x + 1]);
			if (y < AStar::CollumsY - 1) Nodes[y][x].Neighbours.push_back(&Nodes[y + 1][x]);

			
			if (diagonal)  // diagonal steps
			{
				if (y > 0 && x > 0) Nodes[y][x].Neighbours.push_back(&Nodes[y - 1][x - 1]);
				if (y < CollumsY - 1 && x > 0) Nodes[y][x].Neighbours.push_back(&Nodes[y + 1][x - 1]);
				if (y > 0 && x < CollumsX - 1) Nodes[y][x].Neighbours.push_back(&Nodes[y - 1][x + 1]);
				if (y < CollumsY - 1 && x < CollumsX - 1) Nodes[y][x].Neighbours.push_back(&Nodes[y + 1][x + 1]);
			}	
		}
	}

}
void AStar::AStarAlg()
{
	for (int y = 0; y < CollumsY; y++)
	{
		for (int x = 0; x < CollumsX; x++)
		{
			Nodes[y][x].isVisited = false;
			Nodes[y][x].FCost = INFINITY;
			Nodes[y][x].HCost = INFINITY;
			Nodes[y][x].parent = nullptr;
		}
	}
	

	auto GetDist = [](Node* P1, Node* P2) { return sqrt(pow(P2->x - P1->x, 2) + pow(P2->y - P1->y, 2)); };

	Node* CurrentNode = Start;
	Start->HCost = 0.0f;
	Start->FCost = GetDist(Start, End);

	std::vector<Node*> NodesToTest;
	NodesToTest.push_back(Start);

	while (!NodesToTest.empty() && CurrentNode != End)
	{
		std::sort(NodesToTest.begin(), NodesToTest.end(), [](const Node* a, const Node* b) { return a->FCost < b->FCost; });

		while (!NodesToTest.empty() && NodesToTest.front()->isVisited)
			NodesToTest.erase(NodesToTest.begin());

		if (NodesToTest.empty())
			break;

		CurrentNode = NodesToTest.front();
		CurrentNode->isVisited = true;


		for (auto nodeNeighbour : CurrentNode->Neighbours)
		{
			if (!nodeNeighbour->isVisited && !nodeNeighbour->isWall)
				NodesToTest.push_back(nodeNeighbour);

			auto BestNode = CurrentNode->HCost + GetDist(CurrentNode, nodeNeighbour);

			if (BestNode < nodeNeighbour->HCost)
			{
				nodeNeighbour->parent = CurrentNode;
				nodeNeighbour->HCost = BestNode;

				nodeNeighbour->FCost = nodeNeighbour->HCost + GetDist(nodeNeighbour, End);
			}
		}
	}
		
}


