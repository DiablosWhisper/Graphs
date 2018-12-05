#define _USE_MATH_DEFINES
#include "Node.h"
#include <cmath>

Node::Node()
{
	CoordinateX = 0;

	CoordinateY = 0;

	PolarAngle = 0;
}

Node::Node(const Node& Node)
{
	this->CoordinateX = Node.CoordinateX;

	this->CoordinateY = Node.CoordinateY;

	this->PolarAngle = Node.PolarAngle;
}

Node::Node(double CoordinateX, double CoordinateY)
{
	this->CoordinateX = CoordinateX;

	this->CoordinateY = CoordinateY;
}

double Node::GetCoordinateX()
{
	return CoordinateX;
}

double Node::GetCoordinateY()
{
	return CoordinateY;
}

double Node::GetPolarAngle()
{
	return PolarAngle;
}

bool Node::operator < (Node Node)
{
	return this->CoordinateX < Node.CoordinateX ||

		this->CoordinateX == Node.CoordinateX &&

		this->CoordinateY < Node.CoordinateY;
}

Node& Node::operator=(const Node & Node)
{
	this->CoordinateX = Node.CoordinateX;

	this->CoordinateY = Node.CoordinateY;

	this->PolarAngle = Node.PolarAngle;

	return *this;
}

bool Node::operator==(const Node & Node)
{
	return this->CoordinateX == Node.CoordinateX && this->CoordinateY == Node.CoordinateY;
}

bool Node::BelongsToUpperSet(Node FirstNode, Node SecondNode, Node ThirdNode)
{
	return FirstNode.CoordinateX * (SecondNode.CoordinateY - ThirdNode.CoordinateY) +

		SecondNode.CoordinateX * (ThirdNode.CoordinateY - FirstNode.CoordinateY) +

		ThirdNode.CoordinateX * (FirstNode.CoordinateY - SecondNode.CoordinateY) < 0;
}

bool Node::BelongsToLowerSet(Node FirstNode, Node SecondNode, Node ThirdNode)
{
	return FirstNode.CoordinateX * (SecondNode.CoordinateY - ThirdNode.CoordinateY) +

		SecondNode.CoordinateX * (ThirdNode.CoordinateY - FirstNode.CoordinateY) +

		ThirdNode.CoordinateX * (FirstNode.CoordinateY - SecondNode.CoordinateY) > 0;
}

void Node::FindPolarAngle(Node CenterOfMass)
{
	Edge Edge(CenterOfMass, *this);

	if (Edge.GetLengthOfEdge() == 0)
	{
		PolarAngle = 0;
	}
	else
	{
		if (this->CoordinateX > CenterOfMass.GetCoordinateX() && this->CoordinateY >= CenterOfMass.GetCoordinateY())
		{
			PolarAngle = atan((this->CoordinateY - CenterOfMass.GetCoordinateY() / (this->CoordinateX - CenterOfMass.GetCoordinateX())));
		}
		else
		{
			if (this->CoordinateX > CenterOfMass.GetCoordinateX() && this->CoordinateY < CenterOfMass.GetCoordinateY())
			{
				PolarAngle = atan((this->CoordinateY - CenterOfMass.GetCoordinateY() / (this->CoordinateX - CenterOfMass.GetCoordinateX()))) + 2 * M_PI;
			}
			else
			{
				if (this->CoordinateX < CenterOfMass.GetCoordinateX())
				{
					PolarAngle = atan((this->CoordinateY - CenterOfMass.GetCoordinateY() / (this->CoordinateX - CenterOfMass.GetCoordinateX()))) + M_PI;
				}
				else
				{
					if (this->CoordinateX == CenterOfMass.GetCoordinateX() && this->CoordinateY > CenterOfMass.GetCoordinateY())
					{
						PolarAngle = M_PI / 2;
					}
					else
					{
						if (this->CoordinateX == CenterOfMass.GetCoordinateX() && this->CoordinateY < CenterOfMass.GetCoordinateY())
						{
							PolarAngle = 3 * M_PI / 2;
						}
					}
				}
			}
		}
	}
}