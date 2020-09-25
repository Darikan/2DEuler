#ifndef MESH_READ_WRITE
#define MESH_READ_WRITE

#include <string>
#include <iostream>
#include <fstream>
#include "global.h"
#include "configuration.h"
#include <chrono>
#include <ctime>

void writeHeader();
void printFile(std::string fileName);
double getXCoor(std::string line);
double getYCoor(std::string line);
void readGrid(std::string fileName);
void writeMesh(std::string outputFile,bool writeIter,int iteration);
void readCellsValues(std::string meshFile);
void setCellsPoints();
void writeCellsFieldToCSV(std::string fileName);
void submitVectorToCell(double * v,int i, int j);
void writeResidium(std::string resFile, float res[4], int iter);
void writeConfigurationReport();
void writeReport(double Cl, double Re, double runTime);
void writeCl(double Cl,int iteration);
void writePressureOnWall(double pressure, double x);
void printPressureOnWall(int iCellStart, int iCellEnd, int jWall);
#endif

