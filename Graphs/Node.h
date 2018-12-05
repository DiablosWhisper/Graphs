#pragma once

class Node
{
public:

	Node();

	Node(const Node& Node);

	Node(double CoordinateX, double CoordinateY);

	~Node() = default;

	double GetCoordinateX();

	double GetCoordinateY();

	double GetPolarAngle();

	bool operator < (Node Node);

	Node& operator = (const Node& Node);

	bool operator == (const Node& Node);

	bool BelongsToUpperSet(Node FirstNode, Node SecondNode, Node ThirdNode);

	bool BelongsToLowerSet(Node FirstNode, Node SecondNode, Node ThirdNode);

	void FindPolarAngle(Node CenterOfMass);

private:

	double CoordinateX,

		CoordinateY,

		PolarAngle;
};

#include "Edge.h"
