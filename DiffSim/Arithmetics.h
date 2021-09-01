#pragma once
#include <Eigen/Dense>
#include "Point.h"

using namespace Eigen;

namespace Arithmetics {

	Vector2d DisasembleVector(Vector2d TargetVector, Vector2d Base1, Vector2d Base2) {
		Vector2d DisasembledCoords; //Coords of TargetVector in Base1 and Base2
		if (Base1.dot(Base2) == 0) { //Vectors are orthagonal
			DisasembledCoords(0) = (Base1.dot(TargetVector)) / (Base1.norm() * Base1.norm());
			DisasembledCoords(1) = (Base2.dot(TargetVector)) / (Base2.norm() * Base2.norm());
		}
		else {
			Matrix2d A;
			A.col(0) = Base1;
			A.col(1) = Base2;
			DisasembledCoords = A.fullPivHouseholderQr().solve(TargetVector);
		}
		return DisasembledCoords;
	}

	template <typename T>
	Matrix<T,2,1> RoundVector(Vector2d vec) {
		Matrix<T, 2, 1> RoundedVector;
		RoundedVector(0) = static_cast<int>(std::round(vec(0)));
		RoundedVector(1) = static_cast<int>(std::round(vec(1)));
		return RoundedVector;
	}

	class EquationElement {

		double Evaluate() {
			if (linkedValue != NULL) {
				return dKoeffizient * (*linkedValue);
			}
			else {
				return dKoeffizient;
			}
		}

		double dKoeffizient;
		double* linkedValue;
		//represents dKoeffizient * (*linkedValue)
		//if *linked Value is NULL -> its a constant value
	};


}

