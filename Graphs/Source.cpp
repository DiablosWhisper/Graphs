#include <iostream>
#include <vector>
#include <algorithm>
#include "Node.h"
#include "Triangle.h"
#include "Edge.h"

using namespace std;

class Graphs
{
public:

	Graphs()
	{

	}

	~Graphs()
	{

	}

	void ConvexHull()
	{
		if (ListOfDots.size() == 1)
		{
			return;
		}

		sort(ListOfDots.begin(), ListOfDots.end());

		Node UpperCorner = ListOfDots[0],

			LowerCorner = ListOfDots.back();

		vector <Node> UpperSet, LowerSet;

		UpperSet.push_back(UpperCorner);

		LowerSet.push_back(UpperCorner);

		for (int Index = 1; Index < ListOfDots.size(); Index++)
		{
			if (Index == ListOfDots.size() - 1 || ConvexChecker.BelongsToUpperSet(UpperCorner, ListOfDots[Index], LowerCorner))
			{
				while (UpperSet.size() >= 2 && !ConvexChecker.BelongsToUpperSet(UpperSet[UpperSet.size() - 2], UpperSet[UpperSet.size() - 1], ListOfDots[Index]))
				{
					UpperSet.pop_back();
				}

				UpperSet.push_back(ListOfDots[Index]);
			}
			if (Index == ListOfDots.size() - 1 || ConvexChecker.BelongsToLowerSet(UpperCorner, ListOfDots[Index], LowerCorner))
			{
				while (LowerSet.size() >= 2 && !ConvexChecker.BelongsToUpperSet(LowerSet[UpperSet.size() - 2], LowerSet[UpperSet.size() - 1], ListOfDots[Index]))
				{
					LowerSet.pop_back();
				}

				LowerSet.push_back(ListOfDots[Index]);
			}
		}

		for (int Index = 0; Index < UpperSet.size(); Index++)
		{
			ConvexHullDotsSet.push_back(UpperSet[Index]);
		}

		for (int Index = 0; Index < LowerSet.size(); Index++)
		{
			ConvexHullDotsSet.push_back(LowerSet[Index]);
		}

		ConvexHullEdges.push_back(Edge(ConvexHullDotsSet[0],ConvexHullDotsSet[ConvexHullDotsSet.size() - 1]));

		for (int Index = 0; Index < ConvexHullDotsSet.size() - 1; Index++)
		{
			ConvexHullEdges.push_back(Edge(ConvexHullDotsSet[Index],ConvexHullDotsSet[Index + 1]));
		}
	}

	void FindCenterOfMass()
	{
		double CoordinateX = 0,

			CoordinateY = 0;

		for (int Index = 0; Index < ListOfDots.size(); Index++)
		{
			CoordinateX += ListOfDots[Index].GetCoordinateX();
		}

		CoordinateX /= double(ListOfDots.size());

		for (int Index = 0; Index < ListOfDots.size(); Index++)
		{
			CoordinateY += ListOfDots[Index].GetCoordinateY();
		}

		CoordinateY /= double(ListOfDots.size());

		Node Dot(CoordinateX, CoordinateY);

		CenterOfMass = Dot;
	}

	template <typename UnknownType>
	int BelongsToHull(UnknownType& Dot, vector<UnknownType> Vector)
	{
		for (int Index = 0; Index < Vector.size(); Index++)
		{
			if (Vector[Index] == Dot)
			{
				return Index;
			}
		}

		return 0;
	}

	Node FindTheNearestToTheCenter()
	{
		Edge CenterEdge(CenterOfMass, ListOfDots[0]);

		double Length = CenterEdge.GetLengthOfEdge();

		for (int Index = 0; Index < ListOfDots.size(); Index++)
		{
			Edge TemporaryEdge(CenterOfMass, ListOfDots[Index]);

			if (TemporaryEdge.GetLengthOfEdge() < Length)
			{
				CenterEdge = TemporaryEdge;

				Length = TemporaryEdge.GetLengthOfEdge();
			}
		}

		return CenterEdge.GetTheEndOfTheEdge();
	}

	bool DelauneyCondition(Edge ConnectedEdge)
	{
		Edge UniqueEdge(ConnectedEdge.Neighbors[0].GetUniqueNode(ConnectedEdge), ConnectedEdge.Neighbors[1].GetUniqueNode(ConnectedEdge));

		double FirstArgument = (UniqueEdge.GetTheBeginningOfTheEdge().GetCoordinateX() - ConnectedEdge.GetTheEndOfTheEdge().GetCoordinateX())
			
			*(UniqueEdge.GetTheBeginningOfTheEdge().GetCoordinateY() - ConnectedEdge.GetTheBeginningOfTheEdge().GetCoordinateY())
			
			- (UniqueEdge.GetTheBeginningOfTheEdge().GetCoordinateX() - ConnectedEdge.GetTheBeginningOfTheEdge().GetCoordinateX())
			
			*(UniqueEdge.GetTheBeginningOfTheEdge().GetCoordinateY() - ConnectedEdge.GetTheEndOfTheEdge().GetCoordinateY());

		double SecondArgument = (UniqueEdge.GetTheEndOfTheEdge().GetCoordinateX() - ConnectedEdge.GetTheEndOfTheEdge().GetCoordinateX()
			
			* (UniqueEdge.GetTheEndOfTheEdge().GetCoordinateX() - ConnectedEdge.GetTheBeginningOfTheEdge().GetCoordinateX())
			
		    + (UniqueEdge.GetTheEndOfTheEdge().GetCoordinateY() - ConnectedEdge.GetTheEndOfTheEdge().GetCoordinateY())
			
			* (UniqueEdge.GetTheEndOfTheEdge().GetCoordinateY() - ConnectedEdge.GetTheBeginningOfTheEdge().GetCoordinateY()));

		double ThirdArgument = (UniqueEdge.GetTheBeginningOfTheEdge().GetCoordinateX() - ConnectedEdge.GetTheEndOfTheEdge().GetCoordinateX()
			
			* (UniqueEdge.GetTheBeginningOfTheEdge().GetCoordinateX() - ConnectedEdge.GetTheBeginningOfTheEdge().GetCoordinateX())
			
			+ (UniqueEdge.GetTheBeginningOfTheEdge().GetCoordinateY() - ConnectedEdge.GetTheEndOfTheEdge().GetCoordinateY())
			
			* (UniqueEdge.GetTheBeginningOfTheEdge().GetCoordinateY() - ConnectedEdge.GetTheBeginningOfTheEdge().GetCoordinateY()));

		double FourthArgument = (UniqueEdge.GetTheEndOfTheEdge().GetCoordinateX() - ConnectedEdge.GetTheEndOfTheEdge().GetCoordinateX()
			
			* (UniqueEdge.GetTheEndOfTheEdge().GetCoordinateY() - ConnectedEdge.GetTheBeginningOfTheEdge().GetCoordinateY())
			
			- (UniqueEdge.GetTheEndOfTheEdge().GetCoordinateX() - ConnectedEdge.GetTheBeginningOfTheEdge().GetCoordinateX())
			
			* (UniqueEdge.GetTheEndOfTheEdge().GetCoordinateY() - ConnectedEdge.GetTheEndOfTheEdge().GetCoordinateY()));

		if ((FirstArgument * SecondArgument) + (ThirdArgument * FourthArgument) >= 0)
		{
			return true;
		}

		return false;
	}

	void RebuildTriangle(Edge ConnectedEdge,vector<Triangle>& SetOfTriangles)
	{
		int IndexOfFirstTriangle, IndexOfSecondTriangle;

		for (int Index = 0; Index < SetOfTriangles.size(); Index++)
		{
			if (ConnectedEdge.Neighbors[0] == SetOfTriangles[Index])
			{
				IndexOfFirstTriangle = Index;
			}

			if (ConnectedEdge.Neighbors[1] == SetOfTriangles[Index])
			{
				IndexOfSecondTriangle = Index;
			}
		}

		Edge UniqueEdge(ConnectedEdge.Neighbors[0].GetUniqueNode(ConnectedEdge),ConnectedEdge.Neighbors[1].GetUniqueNode(ConnectedEdge));

		SetOfTriangles[IndexOfFirstTriangle] = Triangle(ConnectedEdge.GetTheBeginningOfTheEdge(),UniqueEdge.GetTheBeginningOfTheEdge(),ConnectedEdge.GetTheEndOfTheEdge());

		SetOfTriangles[IndexOfSecondTriangle] = Triangle(ConnectedEdge.GetTheBeginningOfTheEdge(),UniqueEdge.GetTheEndOfTheEdge(),ConnectedEdge.GetTheEndOfTheEdge());
	}

private:

	vector <Node> ListOfDots;

	vector <Node> ConvexHullDotsSet;

	vector <Edge> ConvexHullEdges;

	vector <Node> DelaunayTriangulationDotsSet;

	vector <Node> VoronoyDiagramDotsSet;

	Node ConvexChecker;

	Node CenterOfMass;

	void ConvertAnglesToPolarAngles()
	{
		for (int Index = 0; Index < ListOfDots.size(); Index++)
		{
			ListOfDots[Index].FindPolarAngle(CenterOfMass);
		}
	}

};

void main()
{
	system("pause");
}