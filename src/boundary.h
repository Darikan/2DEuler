#pragma once

#include "global.h"
#include "M_vector.h"
#include "bc.h"
#include <iostream>
#include <fstream>
#include <string>

void loadInitialConditions();
void setBC_wall(int iStart,int iEnd, int jStart, int jEnd, int k);
void setBC_ami(int iStart,int iEnd, int jStart, int jEnd);
void setBC_freeStream(int iStart,int iEnd, int jStart, int jEnd);
void setBC_outlet(int iStart, int iEnd, int jStart, int jEnd,int side);
double scalarProduct(M_vector v1, M_vector v2);
void printBC_field();
void writeBoundaryToCSV(std::string filename);
void setBoundary();
