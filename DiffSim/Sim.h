#pragma once
#include "Grid.h"
#include <vector>

class Sim
{
public:
	std::vector<Grid*> Grids;
	void ExecuteOnAllPoints(void(*Function)(Point& p)) { //Call Execute on Grid Points for all Grids

		for (Grid* _Grid : Grids) { 
			_Grid->ExecuteOnAllGridPoints(Function);
		}

	}
	void ExecuteOnAllExcept(void(*Function)(Point& p), Grid* _Exception) { //Executes on all Points Except in the Grid matching the _Exception Address
		for (Grid* _Grid : Grids) { 
			if (_Grid != _Exception) {
				_Grid->ExecuteOnAllGridPoints(Function);
			}
		}
	}
};

