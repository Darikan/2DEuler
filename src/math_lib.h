#define MATLH_LIB
#ifndef MATH_LIB

#include <cmath>
#include "point.h"
#include "global.h"
#include "M_vector.h"
#include "meshReadWrite.h"

M_vector addM_vectors(M_vector A, M_vector B);
double getCellWallArea(int iCell,int jCell, int k);
double getRectCellArea(int i, int j);
double getCellArea(int iCell, int jCell);
double getLineLength(Point p1, Point p2);
double getDistanceOfPointFromLine(Point p, Point A, Point B);
void getLine(double x1, double y1, double x2, double y2, double &a, double &b, double &c);
double getDist(double pct1X, double pct1Y, double pct2X, double pct2Y, double pct3X, double pct3Y);

M_vector getForceOnWall(int iCell,int jCell,int side);
double getLiftForceOnWall(int i,int jWall,int side);
double getDragForceOnWall(int i,int jWall,int side);
double getWallLength(int i, int j,int side);
Point getCenterOfCell(int iCell, int jCell);
M_vector integrateForceOnWall(int iCellStart,int iCellEnd, int jWall,int side);
double integratePressureOnWall(int iCellStart,int iCellEnd, int jWall);
double calcDragCoefficient();
double calcLiftCoefficient();
double calcReynoldsNumber();
void calcPressureOnWall(int iCellStart, int iCellEnd, int jWall);
void _calcPressureOnWall(int iCellStart, int iCellEnd, int jWall);
double absVal(double val);
float absFloat(double val);
#endif
