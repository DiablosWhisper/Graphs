#pragma once

#include <vector>
#include "Node.h"

class Edge;

class Triangle
{
public:

	Triangle();

	Triangle(Node FirstPeak, Node SecondPeak, Node ThirdPeak);

	~Triangle();

	Node GetUniqueNode(Edge Edge);

	Node* Peaks;

	bool operator == (const Triangle& Triangle);

	void GetCenterOfCircle();

private:

	Node CenterOfCircle;
};

#include "Edge.h"