#include "Triangle.h"

Triangle::Triangle()
{
	Peaks = new Node[3];
}

Triangle::Triangle(Node FirstPeak, Node SecondPeak, Node ThirdPeak)
{
	this->Peaks[0] = FirstPeak;

	this->Peaks[1] = SecondPeak;

	this->Peaks[2] = ThirdPeak;
}

Triangle::~Triangle()
{
	delete[] Peaks;
}

Node Triangle::GetUniqueNode(Edge Edge)
{
	for (int Index = 0; Index < 3; Index++)
	{
		if (Peaks[Index] == Edge.GetTheBeginningOfTheEdge() || Peaks[Index] == Edge.GetTheEndOfTheEdge())
		{
			Index++;
		}
		else
		{
			return Peaks[Index];
		}
	}
}

bool Triangle::operator==(const Triangle& Triangle)
{
	int TemporaryIndex = 0;

	for (int Index = 0; Index < 3; Index++)
	{
		if (this->Peaks[TemporaryIndex] == Triangle.Peaks[Index])
		{
			TemporaryIndex++;
		}
		else
		{
			return false;
		}
	}

	return TemporaryIndex == 3;
}

void Triangle::GetCenterOfCircle()
{
	double Divisioner = 2*(this->Peaks[0].GetCoordinateX()*(this->Peaks[1].GetCoordinateY() - this->Peaks[2].GetCoordinateY()

		+ Peaks[1].GetCoordinateX()*(this->Peaks[2].GetCoordinateY() - this->Peaks[0].GetCoordinateY()) 

		+ Peaks[2].GetCoordinateX()*(this->Peaks[0].GetCoordinateY() - this->Peaks[1].GetCoordinateY())));

	double CoordinateX = ((this->Peaks[0].GetCoordinateX() * this->Peaks[0].GetCoordinateX() + this->Peaks[0].GetCoordinateY() * this->Peaks[0].GetCoordinateY()) * (this->Peaks[1].GetCoordinateY() - this->Peaks[2].GetCoordinateY()) 
		
		+ (this->Peaks[1].GetCoordinateX() * this->Peaks[1].GetCoordinateX() + this->Peaks[1].GetCoordinateY() * this->Peaks[1].GetCoordinateY()) * (this->Peaks[2].GetCoordinateY() - this->Peaks[0].GetCoordinateY())
		
		+ (this->Peaks[2].GetCoordinateX() * this->Peaks[2].GetCoordinateX() + this->Peaks[2].GetCoordinateY() * this->Peaks[2].GetCoordinateY()) * (this->Peaks[0].GetCoordinateY() - this->Peaks[1].GetCoordinateY())) /Divisioner;

	double CoordinateY = ((this->Peaks[0].GetCoordinateX() * this->Peaks[0].GetCoordinateX() + this->Peaks[0].GetCoordinateY() * this->Peaks[0].GetCoordinateY()) * (this->Peaks[2].GetCoordinateX() - this->Peaks[1].GetCoordinateX())

		+ (this->Peaks[1].GetCoordinateX() * this->Peaks[1].GetCoordinateX() + this->Peaks[1].GetCoordinateY() * this->Peaks[1].GetCoordinateY()) * (this->Peaks[0].GetCoordinateX() - this->Peaks[2].GetCoordinateX())

		+ (this->Peaks[2].GetCoordinateX() * this->Peaks[2].GetCoordinateX() + this->Peaks[2].GetCoordinateY() * this->Peaks[2].GetCoordinateY()) * (this->Peaks[1].GetCoordinateX() - this->Peaks[0].GetCoordinateX())) / Divisioner;

	CenterOfCircle = Node(CoordinateX,CoordinateY);
}