#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "global.h"

double getConfDoubleValue(std::string line, int nline);
double getConfIntValue(std::string line, int nline);
std::string getConfStringValue(std::string line, int nline);
std::string getValueType(std::string sline, int nline);
void readConfig(std::string configFile);
void printConfiguration();
std::string getFileName();
void setFields();
void setupFiles();
void createCase();
void generatePlotScript();
#endif
