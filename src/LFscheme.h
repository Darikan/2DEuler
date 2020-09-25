#ifndef LF_SCHEME_H
#define LF_SCHEME_H

#include "M_vector.h"
#include "math_lib.h"
#include "cell.h"
#include "point.h"
#include "meshReadWrite.h"
#include "boundary.h"
#include <vector>
#include "global.h"
#include <string>
#include <iostream>
#include "postproc.h"


void printVector(std::string name,double * v,int size);
void increaseVector(double v1[4], double v2[4]);
double * addVectors(double v1[4], double v2[4]);
double * subtractVectors(double v1[4], double v2[4]);
double * multiplyVector(double a, double v1[4]);
double * totalFlux(int iCell, int jCell,double cellArea, double dt, double * W,bool debug);
void runCalculation(bool debug);
void testFields();
double getPressureOnWall();
void residUpdate(float resid[4], int iter);

#endif
