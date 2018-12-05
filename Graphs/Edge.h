#pragma once

#include "Node.h"
#include <vector>
class Triangle;

class Edge
{
public:

	Edge();

	Edge(Node FirstCoordinate, Node SecondCoordinate);

	~Edge();

	double GetLengthOfEdge();

	Node GetTheBeginningOfTheEdge();

	Node GetTheEndOfTheEdge();

	Edge operator = (const Edge& Edge);

	bool operator == (const Edge& Edge);

	std::vector<Triangle> Neighbors;

private:

	Node * Dots;
};

#include "Triangle.h"

