#include "configuration.h"

using namespace std;



string getFileName(){
    string file = __FILE__;
    size_t index;
    for(index = file.size();index >0; index--){
        if(file[index - 1] == '\\' || file[index - 1] == '/') break;
    }
    return file.substr(index);
}


double getConfDoubleValue(string line, int nline){
	int valStart = 0;
	string out = "";
	for(size_t i = 0;i<line.length();i++){
		if(line[i] == ' '){
			valStart = i+1;
		}
	}
	if(valStart == 0) cout << "#w: no value in configuration file on line " << nline << " (line value: \""<< line << "\")"<< endl;
	//cout << "gcdv: " << nline << " " << line << "; "<< valStart <<"; "<< line.length()-valStart << endl;
	out = line.substr(valStart,line.length()-valStart);
	//cout << out << ";" << endl;
	return stof(out.c_str());
}
double getConfIntValue(string line, int nline){
	int valStart = 0;
	string out;
	double res;
	for(size_t i = 0;i<line.length();i++){
		if(line[i] == ' '){
			valStart = i+1;
		}
	}
	if(valStart == 0) cout << "#w: no value in configuration file on line " << nline << " (line value: \""<< line << "\")"<< endl;
	//cout << "gciv: " << nline << " " << line << "; "<< valStart <<"; "<< line.length() - valStart << endl;
	out = line.substr(valStart,line.length()-valStart);
	//cout << out << ";" << endl;
	res = stof(out.c_str());
	return res;
}
string getConfStringValue(string line, int nline){
	int valStart = 0;
	for(size_t i = 0;i<line.length();i++){
		if(line[i] == ' '){
			valStart = i+1;
		}
	}
	if(valStart == 0) cout << "#w: no value in configuration file on line " << nline << " (line value: \""<< line << "\")"<< endl;
	line = line.substr(valStart,sizeof(line));
	return line;
}
bool getConfBooleanValue(string line, int nline){
	string input;
	int valStart = 0;
	for(size_t i = 0;i<line.length();i++){
		if(line[i] == ' '){
			valStart = i+1;
		}
	}
	input = line.substr(valStart,sizeof(line));
	if(valStart == 0) cout << "#w: no value in configuration file on line " << nline << " (line value: \""<< line << "\")"<< endl;
	if(input == "true") return true;
	else return false;
}
string getValueType(string sline, int nline){
	int valEnd = 0;
	for(size_t i = 0;i<sline.length();i++){
		if(sline[i] == ' '){
			valEnd = i;
		}
	}
	if(valEnd == 0) cout << "#w: no value type in configuration file on line " << nline << " (line value: \""<< sline << "\")"<< endl;
	sline = sline.substr(0,valEnd);
	return sline;
}
void readConfig(string configFile){
	


	enum class Parameters{
	_null,
	_npointsI,
	_npointsJ,
	_meshFileCSV,
	_residualsFile,
	_meshFile,
	_test,
	_ux,
	_uy,
	_initial_ux,
	_initial_uy,
	_p,
	_T,
	_eps,
	_r,
	_kappa,
	_timeStep,
	_startTime,
	_endTime,
	_writeInterval,
	_resInterval,
	_debug,
	_report,
	_reportName
	};

	std::map<string, Parameters> s_map =
	{
		{"", Parameters::_null},
		{"npointsI", Parameters::_npointsI},
		{"npointsJ", Parameters::_npointsJ},
		{"meshFileCSV", Parameters::_meshFileCSV},
		{"residualsFile", Parameters::_residualsFile},
		{"meshFile", Parameters::_meshFile},
		{"test", Parameters::_test},
		{"ux", Parameters::_ux},
		{"uy", Parameters::_uy},
		{"initial_ux", Parameters::_initial_ux},
		{"initial_uy", Parameters::_initial_uy},
		{"p", Parameters::_p},
		{"T", Parameters::_T},
		{"r", Parameters::_r},
		{"kappa", Parameters::_kappa},
		{"timeStep", Parameters::_timeStep},
		{"startTime", Parameters::_startTime},
		{"endTime", Parameters::_endTime},
		{"writeInterval", Parameters::_writeInterval},
		{"resInterval", Parameters::_resInterval},
		{"eps", Parameters::_eps},
		{"debug", Parameters::_debug},
		{"report", Parameters::_report},
		{"reportName", Parameters::_reportName}
	};	
	
	ifstream file;
	file.open(configFile);
	string line;
	int i = 1;
	if(file.is_open()){
		while(getline(file,line)){
			if(line[0] == '#') continue;
			//cout << "#i: " << line << endl;
			Parameters pars = s_map[getValueType(line,i)];
			//cout << getValueType(line,i) << ";" << endl;
			
			switch(pars){
				case Parameters::_npointsI: npointsI = getConfIntValue(line,i); break;
				case Parameters::_npointsJ: npointsJ = getConfIntValue(line,i); break;
				case Parameters::_meshFileCSV: meshFileCSV = getConfStringValue(line,i); break;
				case Parameters::_residualsFile: residualsFile = getConfStringValue(line,i); break;
				case Parameters::_meshFile: meshFile = getConfStringValue(line,i); break;
				case Parameters::_test: test = getConfStringValue(line,i); break;
				case Parameters::_ux: ux = getConfDoubleValue(line,i); break;
				case Parameters::_uy: uy = getConfDoubleValue(line,i); break;
				case Parameters::_initial_ux: initial_ux = getConfDoubleValue(line,i); break;
				case Parameters::_initial_uy: initial_uy = getConfDoubleValue(line,i); break;
				case Parameters::_p: p = getConfDoubleValue(line,i); break;
				case Parameters::_T: T = getConfDoubleValue(line,i); break;
				case Parameters::_r: r = getConfDoubleValue(line,i); break;
				case Parameters::_kappa: kappa = getConfDoubleValue(line,i); break;
				case Parameters::_timeStep: timeStep = getConfDoubleValue(line,i); break;
				case Parameters::_startTime: startTime = getConfDoubleValue(line,i); break;
				case Parameters::_endTime: endTime = getConfDoubleValue(line,i); break;
				case Parameters::_writeInterval: writeInterval = getConfIntValue(line,i); break;
				case Parameters::_resInterval: resInterval = getConfIntValue(line,i); break;
				case Parameters::_eps: eps = getConfDoubleValue(line,i); break;
				case Parameters::_debug: debug = getConfBooleanValue(line,i); break;
				case Parameters::_report: report = getConfBooleanValue(line,i); break;
				case Parameters::_reportName: reportName = getConfStringValue(line,i); break;
				default: cout << "#w: unknown value or value type on line "<< i << " (readConfig() in " << getFileName() << ")" << endl;
			}
			/*if(getValueType(line,i) == "p"){
			p = 103;
			cout << "found p" << endl;
			}*/
			pars = s_map[""];				
			i++;
		}
	}
	else cout << "#e: file \"" << configFile << "\" didn't open (readConfig() in " << getFileName() << ")" << endl;
	file.close();
	//cout << "in read: " << test << endl;
}
void setupFiles(){
	//TODO: make postproc folder
	ofstream file;
	file.open("./" + reportName + "/residuals.csv");
	file << "iteration,rho_x,rho_y,p,rho,e" << endl;
	file.close();
	file.open("./" + reportName + "/cls.csv");
	file << "iteration,Cl" << endl;
	file.close();
	file.open("./" + reportName + "/wallPressure.csv");
	file << "x,pressure" << endl;
	file.close();

	createCase();
	generatePlotScript();
}
void printConfiguration(){
	string d;	
	if(debug) d = "true";
	else d = "false";
	cout << "---configuration---" << endl;
	cout << "npointsI:" << npointsI << "; npointsJ:" << npointsJ << "; meshFile:" << meshFile << "; meshFileCSV:" << meshFileCSV  << "residualsFile: " << residualsFile << endl <<
	"initials: ux,uy,in_ux,in_uy,p,T,r,kappa:" << ux << "," << uy << "," << initial_ux << "," << initial_uy << "," << p << "," << T << "," << r << "," << kappa << ", debug: " << d << endl <<
	"timeStep: " << timeStep << ", startTime: " << startTime << ", endTime: " << endTime << ", writeInterval: " << writeInterval << ", residiumWriteInterval: " << resInterval << endl <<
	"eps: " << eps << endl;
	cout << "--------end--------" << endl << endl;
}
void setFields(){
//	vector<vector<Point>> grid(npointsI, vector<Point> (npointsJ));
//	vector<vector<Cell>> cells(npointsI+1, vector<Cell> (npointsJ+1));
//	grid = vector<vector<Point>>(npointsI, vector<Point> (npointsJ));
//	cells = vector<vector<Cell>>(npointsI+1, vector<Cell> (npointsJ+1));
	grid = new Point*[npointsI];
	for(int i=0;i<npointsI;i++){
		grid[i] = new Point[npointsJ];
	}
	//cout << "npI: "<< npointsI << endl;

	cells = new Cell*[npointsI+1];
	for(int i=0;i<npointsI+1;i++){
		cells[i] = new Cell[npointsJ+1];
	}
	cout << "cells: " << (npointsJ+1)*(npointsI+1) << endl;
}
void createCase(){
	string caseDir = "mkdir -p ./" + reportName;
	system(caseDir.c_str());
}
void generatePlotScript(){
	string fileName;
	fileName = "./" + reportName + "/plotResiduals.gp";	
	ofstream file;
	file.open(fileName);
	file << "set output 'graphs.eps'" << endl;
	file << "set size 2,2" << endl;
	file << "set multiplot layout 1, 2" << endl;
	file << "set grid" << endl;
	file << endl;	

	file << "set title \"Convergence process\"" << endl;
	file << "set xlabel \"Iterations\"" << endl;
	file << "set ylabel \"Residuals\"" << endl;
	file << "set logscale y" << endl;
	file << "set datafile separator \",\" " << endl;
	file << "plot \"residuals.csv\" using 1:2  with lines title \"rho_x\", '' using 1:3 with lines title \"rho_y\", '' using 1:4 with lines title \"p\", '' using 1:5 with lines title \"rho\", '' using 1:6 with lines title \"e\"" << endl;
	file << endl;	

	file << "set title \"Cl coefficient\"" << endl;
	file << "unset logscale y" << endl;
	file << "set xlabel \"Iterations\"" << endl;
	file << "set ylabel \"Cl\"" << endl;
	file << "plot \"cls.csv\" using 1:2 with lines title \"Cl\"" << endl;
	file << endl;
	file << "unset multiplot" << endl;
	file << "pause mouse" << endl;

	file.close();

}



