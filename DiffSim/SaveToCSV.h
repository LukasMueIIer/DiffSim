#pragma once
#include <fstream>
#include <stdio.h>
#include "Point.h"

using namespace std;

namespace CSV {

	void CSVWriter(Point& p, int iMode) { //you should allmost never call this function directly, use its sub implementations
		static fstream file; //Handle of file to write into
		static int iFileCount; //Amount of existing files
		char cBuffer[50]; //for string manipulation
		static bool opened; //to check if file is allready opened wenn NewCSVStep is called, if so file is closed

		switch (iMode)
		{
		case -1: //Setup CSVWriter
			iFileCount = 0;
			break;
		case 0: //open new file with apropriat number
			if (opened) { //close allready opened file, probably forgot to call close csv
				file.close();
			}
			sprintf_s(cBuffer, 50, "temp%d.csv", iFileCount);
			file.open(cBuffer, ios::out);
			file << "X ; Y ; T ; dT ;" << endl;
			opened = true;
			++iFileCount;
			break;
		case 1: //Write Point Data to CSV
			if (opened) {
				file << p.vPosition(0) << " ; " << p.vPosition(1) << " ; " << p.T << ";" << p.dT << ";" << endl;
			}
			break;
		case 2: //Close current file
			if (opened) { //close allready opened file, probably forgot to call close csv
				file.close();
				opened = false;
			}
			break;
		default:
			break;
		}
	}
	void SetUpCSV() { //Set up everything so csv writer can be used
		Point p;
		CSVWriter(p, -1);
	}

	void NewCSVStep() { //Create a new CSV File 
		Point p;
		CSVWriter(p, 0);
	}

	void WritePointCSV(Point& p) {
		CSVWriter(p, 1);
	}

	void CloseCSV() {
		Point p;
		CSVWriter(p, 2);
	}

}

