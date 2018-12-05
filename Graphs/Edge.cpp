#include "Edge.h"
#include <cmath>

using namespace std;

Edge::Edge()
{
	Dots = new Node[2];
}

Edge::~Edge()
{
	delete[] Dots;
}

Edge::Edge(Node FirstCoordinate, Node SecondCoordinate)
{
	this->Dots[0] = FirstCoordinate;

	this->Dots[1] = SecondCoordinate;
}

double Edge::GetLengthOfEdge()
{
	return sqrt(pow(Dots[1].GetCoordinateX() - Dots[0].GetCoordinateX(), 2) + pow(Dots[1].GetCoordinateY() - Dots[0].GetCoordinateY(), 2));
}

Node Edge::GetTheBeginningOfTheEdge()
{
	return Dots[0];
}

Node Edge::GetTheEndOfTheEdge()
{
	return Dots[1];
}

Edge Edge::operator= (const Edge& Edge)
{
	this->Dots[0] = Edge.Dots[0];

	this->Dots[1] = Edge.Dots[1];

	this->Neighbors.clear();

	for (int Index = 0; Index < Edge.Neighbors.size(); Index++)
	{
		Neighbors.push_back(Edge.Neighbors[Index]);
	}

	return *this;
}

bool Edge::operator== (const Edge& Edge)
{
	return (this->Dots[0] == Edge.Dots[0] && this->Dots[1] == Edge.Dots[1]);
}