#pragma once
#include <Eigen/Dense>
#include <vector>
#include "Arithmetics.h"

using namespace Eigen;

class Point //Basic Class for all actual Points
{
public:

	Point(Vector2d vPos = Vector2d(0, 0), bool isVal = true, double Temp = 0) {
	
	}

	std::vector<Point&> closePoints;

	bool isValid; //Determines wether a point is a valid part of the simultion
	Eigen::Vector2d vPosition; //The Position of the Point 
	
	//Temperature
	bool valT; //If this point should be used for temp calculations
	double T; //The Temperature of the Point
	double dT; //Derivative of Temperature
	std::vector<Arithmetics::EquationElement> TEqaution; //Vector representing the equation for calculationg dT;

	//virtual vector? StaticCalc() = 0; //Implement increment equation into a sparce matrix
 };

