#pragma once

#include <vector>
#include <string>
#include "cell.h"
#include "point.h"
#include "bc.h"

extern int npointsI;
extern int npointsJ;
extern std::string meshFileCSV;
extern std::string meshFile;
extern std::string residualsFile;
extern std::string test;
extern std::string reportName;
extern double ux,uy,initial_ux,initial_uy,p,T,timeStep,endTime,startTime,eps,r,kappa;
extern bool debug,report;
extern int npoints;
extern int ncells;
extern int resInterval,writeInterval;
#define PI 3.14159

//extern std::vector<std::vector<Point>> grid;
//extern std::vector<std::vector<Cell>> cells;

extern Point** grid;
extern Cell** cells;
extern std::vector<BC> bc;
