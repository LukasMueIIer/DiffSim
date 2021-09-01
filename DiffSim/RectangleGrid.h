#pragma once
#include "Grid.h"
#include "Point.h"
#include <vector>
#include "Arithmetics.h"

template <int iXPoints, int iYPoints> //determines the total amount of points and how many points are used for each axis
class RectangleGrid : public Grid
{
public:
	RectangleGrid(Vector2d vSeed, Vector2d vXMax, Vector2d vYMax) { //Seed is Pos of Point 0,0; vXMax is Pos of Point xMax,0; vYMax is Pos of Point 0,yMax;
		dX = (vXMax - vSeed) / (iXPoints - 1);
		dY = (vYMax - vSeed) / (iYPoints - 1);
		for (int x = 0; x < iXPoints; x++) {
			for (int y = 0; y < iYPoints; y++) {

				Vector2d Pos = vSeed + x * dX + y * dY; //Position of Point
				Points[x][y] = Point(Pos , true, 0);

			}
		}
	}

	Vector2d dX, dY; //increments for x and y axis
	Point Points[iXPoints][iYPoints];
	void ExecuteOnAllGridPoints(void(*Function)(Point& p)) {
		for (int x = 0; x < iXPoints; x++) {
			for (int y = 0; y < iYPoints; y++) {

				
				if (Points[x][y].isValid) {
					Function(Points[x][y]);
				}

			}
		}


	}

	std::vector<Point*> PointsInRange(Vector2d vSeed, double dMaxDist) {
		std::vector<Point*> _PointsInRange; //Holds all Points in range

		int imX, imY; //max amount of X steps and Y steps from center
		imX = static_cast<int>(std::ceil(dMaxDist / dX.norm()));
		imY = static_cast<int>(std::ceil(dMaxDist / dY.norm()));
		
		//connect to Seed Point
		Vector2i ZeroToSeed = Arithmetics::RoundVector<int>(Arithmetics::DisasembleVector(vSeed - Points[0][0].vPosition, dX, dY));	

		//Attach Points to Vector Range
		int iXMin, iXMax, iYMin, iYMax;
		iXMin = ZeroToSeed(0) - imX;
		if (iXMin < 0) {  //iXMin cannt be negative
			iXMin = 0;
		}
		iXMax = ZeroToSeed(0) + imX; //iXMax cant be larger than iXPoints
		if (iXMax > iXPoints) {
			iXMax = iXPoints;
		}
		iYMin = ZeroToSeed(1) - imY;
		if (iYMin < 0) {  //iYMin cannt be negative
			iYMin = 0;
		}
		iYMax = ZeroToSeed(0) + imY; //iYMax cant be larger than iXPoints
		if (iYMax > iYPoints) {
			iYMax = iYPoints;
		}

		//Actually attach the points
		_PointsInRange.reserve((iXMax - iXMin) * (iYMax - iYMin)); //reserve for perfomance
		for (int x = iXMin; x < iXMax; ++x) {
			for (int y = iYMin; y < iYMax; ++y) {

				if ((Points[x][y].vPosition - vSeed).norm() <= dMaxDist ) {
					_PointsInRange.push_back(&Points[x][y]);
				}

			}
		}

		_PointsInRange.shrink_to_fit();

		return _PointsInRange;
	}

};

