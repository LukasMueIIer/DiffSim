// DiffSim.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "Point.h"
#include <Eigen/Dense>
#include "Grid.h"
#include "RectangleGrid.h"
#include "SaveToCSV.h"
#include "Arithmetics.h"
#include <vector>
#include "Sim.h"

using namespace std;

int main()
{
	Sim mainSim;

	CSV::SetUpCSV(); //Set up CSV writer

	Vector2d v1, v2, v3;
	v1 << 0, 0;
	v2 << 1, 0;
	v3 << 0, 1;
	RectangleGrid<330,330> RG(v1,v2,v3);

	mainSim.Grids.push_back(&RG);

	CSV::NewCSVStep();


	mainSim.ExecuteOnAllPoints(CSV::WritePointCSV);

	CSV::CloseCSV();
	CSV::NewCSVStep();

	std::vector<Point*> vp = RG.PointsInRange(Vector2d(0.5,0.5), 0.2);

	for (Point* p : vp) {
		
		p->T = 3;

	}

	RG.ExecuteOnAllGridPoints(CSV::WritePointCSV);

	CSV::CloseCSV();
	CSV::NewCSVStep();
	mainSim.ExecuteOnAllExcept(CSV::WritePointCSV, &RG);
	CSV::CloseCSV();

}

// Programm ausführen: STRG+F5 oder "Debuggen" > Menü "Ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
