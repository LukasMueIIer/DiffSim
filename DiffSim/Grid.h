#pragma once
#include "Point.h"
#include <vector>
#include <Eigen/Dense>

using namespace Eigen;

class Grid
{
public:
	
	virtual void ExecuteOnAllGridPoints(void(*Function)(Point& p)) = 0; //Executes Function on all valid Points
	virtual std::vector<Point*> PointsInRange(Vector2d vSeed, double dMaxDist) = 0; //Returns a vector holding all points that are equal or less distant than dMaxDist from vSeed 

};

