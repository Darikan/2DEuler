#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <tgmath.h>
#include <map>
#include <chrono>
#include <ctime>
#include "boundary.h"
#include "cell.h"
#include "LFscheme.h"
#include "math_lib.h"
#include "meshReadWrite.h"
#include "M_vector.h"
#include "point.h"
#include "configuration.h"
#include "global.h"
#include "postproc.h"


using namespace std;
using namespace std::chrono;

//vector<vector<Point>> grid(npointsI, vector<Point> (npointsJ));
//vector<vector<Cell>> cells(npointsI+1, vector<Cell> (npointsJ+1));
//std::vector<std::vector<Cell>> cells;
//std::vector<vector<Point>> grid;
std::vector<BC> bc;

Point** grid;
Cell** cells;

int npointsI;
int npointsJ;
std::string meshFileCSV;
std::string meshFile;
std::string residualsFile;
std::string test;
std::string reportName;
double ux,uy,initial_ux, initial_uy, p,T,timeStep,endTime,startTime,eps,r,kappa;
int resInterval,writeInterval;
bool debug,report;
int ncells,npoints;

int main(){

	auto start = high_resolution_clock::now(); 
	string file = __FILE__;
	size_t index;
	for(index = file.size();index>0; index--){
		if(file[index - 1] == '\\' || file[index - 1] == '/') break;
	}

	cout << "### Euler2D ###" << endl << endl;

//	cout << p.getX() << endl;
	readConfig("control.cfg");
	setFields(); //initialize array fields
	setupFiles();
	printConfiguration();
	readGrid(meshFileCSV);

	meshFile = "./" + reportName + "/" + reportName.c_str() + ".vtk";	
	loadInitialConditions();
	

	cout << "setting boundary..." << endl;

	setBoundary();

/*
	setBC_freeStream(0,0,1,bc_jCell);
	setBC_outlet(bc_iCell,bc_iCell,1,bc_jCell,-1);
	setBC_wall(1,bc_iCell-1,1,1,2);
	setBC_wall(1,bc_iCell-1,bc_jCell-1,bc_jCell-1,0);
*/
	cout << "Done" << endl;	
//	printBC_field();		
//	for(int c=1;c<12;c++) cells[1][c].setrho_u(20);
	cout << "writing CSV files..." << endl;
	writeBoundaryToCSV("bc.csv");
	writeCellsFieldToCSV("cellsrho.csv");

	writeMesh(meshFile,false,0);
	//readCellsValues(meshFile);
	//checkBC();	
	writeConfigurationReport();


	cout << "Done" << endl; 
	cout << endl;
	cout << "---calculation---" << endl;
	cout << endl;
	runCalculation(debug);

	writeMesh(meshFile,false,0);
	cout  << endl;
	//hello();
/*
//	cout << sizeof(cells) << endl; 	
//	setCellsPoints();
	//printgrid();
//	cout << cells[0][0].getrho() << endl;
//	cout << getConfDoubleValue("npo 156",0) << endl;
 	
*/
	cout << "cell area: " << getCellArea(1,1) << endl;
//	cout << "rect cell area: " << getRectCellArea(1,1) << endl;
	cout << "p on cell 1,1: " << cells[1][1].calc_p(kappa) << endl;
	cout << endl;
	
	cout << "pressure on bottom wall: " << integratePressureOnWall(25,78,34) << endl;
	cout << "Lift on bottom wall: " << integrateForceOnWall(25,78,34,2).getY() << endl;
	cout << endl;
	cout << "pressure on top wall: " << integratePressureOnWall(79,132,34) << endl;
	cout << "Lift on top wall: " << integrateForceOnWall(79,132,34,2).getY() << endl;

	double Re = calcReynoldsNumber();
	double Cl = calcLiftCoefficient();
	printPressureOnWall(25,78,34);
	cout << endl;
	printPressureOnWall(79,132,34); 
	calcPressureOnWall(25,78,34);
	cout << "Re: " << Re << endl;
	cout << "Cl: " << Cl << endl;

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start); 
	double runTime = duration.count() / 1000000.;
	cout << "writing report for " + reportName + "..." << endl;
	writeReport(Cl,Re,runTime);
	
//	int a = 0;
//	int b = 0;
//	cout << "a: " << grid[a][b].getX() << "," << grid[a][b].getY() << " b: " << grid[a+1][b].getX() << "," << grid[a+1][b].getY() <<
//	" c: " << grid[a+1][b+1].getX() << "," << grid[a+1][b+1].getY() << " d: " << grid[a][b+1].getX() << "," << grid[a][b+1].getY();
	//delete[] cells;
	//delete[] grid;
	cout << "clearing memory..." << endl;
	testFields();	
	cout << "DONE!";
	cout << endl;
	return 0;
}
