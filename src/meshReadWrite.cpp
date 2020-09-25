#include "meshReadWrite.h"

using namespace std;

void writeHeader(){ // ------needs rework----------
	ofstream file;
	file.open(meshFile); //TODO mash file
	file << "# vtk DataFile Version 3.0" << endl << "vtk output" << endl << "ASCII" << endl << "DATASET STRUCTURED_GRID" << endl
	<< "DIMENSIONS "<< npointsJ << " " << npointsI << " 1" << endl << "POINTS float " << npointsI*npointsJ << endl;
	file.close();
}

void printFile(string fileName){
	ifstream file;
	string line;
	file.open(fileName);
	if(file.is_open()){
		while(getline(file,line)){
			cout << line << '\n'; 			
		}
		file.close();
	}
	else cout << "file didn't open";
}
double getXCoor(string line){
	size_t i = 0;
	int xend = 1;
	string coor;
//	cout << line << endl;
	for(i=0;i<line.length();i++){
		if(line[i] == ','){
			xend = i;
			//cout << "xend: " << xend << endl;	
			break;
		}
	}
	coor = line.substr(0,xend);
	return atof(coor.c_str());
}

double getYCoor(string line){
	size_t i;
	int ystart = 0;
	int c = 0;
	int yend = 0;
	string coor;
	for(i=0;i<line.length();i++){
		if(line[i] == ',') {
			c++;
			if(c==1) ystart = i+1;			
			if(c==2) yend = i-ystart;
		}
	}
	//cout << c << "," << ystart << "," << yend << endl;
	coor = line.substr(ystart,yend);
	return atof(coor.c_str());
}

void readGrid(string fileName){
	ifstream file;
	string line;
	int i = 0;
	int j = 0;
	int lim = 0;	
	file.open(fileName);
	getline(file,line);
	if(file.is_open()){
		for(i=0;i<npointsI;i++){ //156
			for(j=0;j<npointsJ;j++){ //35
				getline(file,line);
				//cout << line << endl;	
				//xCoordinate = getXCoor(line);
				//yCoordinate = getYCoor(line);		
				grid[i][j].set(getXCoor(line),getYCoor(line));
				//cout << i << ": " << xCoordinate << ", " << j << " " << yCoordinate << endl;
				lim++;		
			}
		}
		file.close();
	}
	else cout << "file didn't open" << endl;
	cout << "rows loaded: " << lim << ", final i: " << i-1 << ", final j: " << j-1 << endl;
}
void writeMesh(string outputFile,bool writeIter, int iteration){
	npoints = npointsI*npointsJ;
	ncells = (npointsI-1) * (npointsJ-1);
	cout << "Writing mesh to " + outputFile + "..." << endl;	
	ofstream file;
	file.open(meshFile);
	//header
	//file << "# vtk DataFile Version 3.0" << endl << "vtk output" << endl << "ASCII" << endl << "DATASET STRUCTURED_GRID" << endl
	//<< "DIMENSIONS 35 156 1" << endl << "POINTS "<< npoints << " float" << endl;

	file << "# vtk DataFile Version 3.0" << endl << "vtk output" << endl << "ASCII" << endl << "DATASET STRUCTURED_GRID" << endl
	<< "DIMENSIONS "<< npointsJ << " " << npointsI << " 1" << endl << "POINTS " << npointsI*npointsJ << " float" << endl;

	int i,j;
	for(i=0;i<npointsI;i++){
		for(j=0;j<npointsJ;j++){
			file << grid[i][j].getX() << " " << grid[i][j].getY() << " 0" << endl; 
		}
	}
	
	file << "CELL_DATA " << ncells << endl << "FIELD FieldData 8" << endl;

	file << "rho 1 " << ncells << " float" << endl;
	for(i=1;i<npointsI;i++) {
		for(j=1;j<npointsJ;j++){
			file << cells[i][j].getrho() << endl;
		}
	}

	file << "rho_u 1 " << ncells  << " float" << endl;
	for(i=1;i<npointsI;i++) {
		for(j=1;j<npointsJ;j++){
			file << cells[i][j].getrho_u() << endl;
		}
	}

	file << "rho_v 1 " << ncells  << " float" << endl;
	for(i=1;i<npointsI;i++) {
		for(j=1;j<npointsJ;j++){
			file << cells[i][j].getrho_v() << endl;
		}
	}

	file << "e 1 " << ncells  << " float" << endl;
	for(i=1;i<npointsI;i++) {
		for(j=1;j<npointsJ;j++){
			if(i == 155 && j == 1 && writeIter) {
				cout << "#i: iteration " << iteration << endl;
				//file << iteration << endl;
			}
			else file << cells[i][j].gete() << endl;
		}
	}

	file << "p 1 " << ncells  << " float" << endl;
	for(i=1;i<npointsI;i++) {
		for(j=1;j<npointsJ;j++){
			file << cells[i][j].calc_p(kappa) << endl;
 
		}
	}

	file << "Ux 1 " << ncells  << " float" << endl;
	for(i=1;i<npointsI;i++) {
		for(j=1;j<npointsJ;j++){
			file << cells[i][j].calc_u() << endl;
		}
	}
	file << "Uy 1 " << ncells  << " float" << endl;
	for(i=1;i<npointsI;i++) {
		for(j=1;j<npointsJ;j++){
			file << cells[i][j].calc_v() << endl;
		}
	}
	file << "U 3 " << ncells  << " float" << endl;
	for(i=1;i<npointsI;i++) {
		for(j=1;j<npointsJ;j++){
			file << cells[i][j].calc_u() << " " << cells[i][j].calc_v() << " 0" << endl;
		}
	}
	file.close();
	cout << "Mesh write done" << endl;
}

void readCellsValues(string meshFile){
	ifstream file;
	string line;
	int k = 7;
	int i,j;
	ncells = (npointsI-1) * (npointsJ-1);
	string field1 = "rho 1 " + to_string(ncells) + " float";
	string field2 = "rho_u 1 " + to_string(ncells) + " float";
	string field3 = "rho_v 1 " + to_string(ncells) + " float";
	string field4 = "e 1 " + to_string(ncells) + " float";
	int field1start = 0;
	int field2start = 0;
	int field3start = 0;
	int field4start = 0;

	file.open(meshFile);
	if(file.is_open()){
		for(i=0;i<6;i++) getline(file,line);
			while(getline(file,line)){
				if(line == field1){
					k++;
					field1start = k;
					//getline(file,line);
					cout << "#i: rho: separator on line " << k-1 << endl;
					for(j=1;j<npointsJ;j++){ //155
						for(i=1;i<npointsI;i++){ //34
							if(getline(file,line) && k >= field1start && k < (field1start + ncells + 1)){
								//cout << k << endl;
								cells[i][j].setrho(atof(line.c_str()));
							}
							if(i==npoints-3 && j==npointsJ-3) cout << "34,155: "<< line << endl;
							//else cout << "#e: out of lines in file (readCells() in " << getFileName() << ")" << endl;
							k++;
							//10740
						}
					}
				}
				if(line == field2){
				field2start = k;
				cout << "#i: rho_u: separator on line " << k-1 << endl;
					for(j=1;j<npointsJ;j++){
						for(i=1;i<npointsI;i++){
							if(getline(file,line) && k >= field2start && k < (field2start + ncells + 1)){
								//cout << k << endl;
								cells[i][j].setrho_u(atof(line.c_str()));
							}
	
							//else cout << "#e: out of lines in file (readCells() in " << getFileName() << ")" << endl;
							k++;
						}
					}
				}
				if(line == field3){
				field3start = k;
				cout << "#i: rho_v: separator on line " << k-1 << endl;
					for(j=1;j<npointsJ;j++){
						for(i=1;i<npointsI;i++){
							if(getline(file,line) && k >= field3start && k < (field3start + ncells + 1)){
								//cout << k << endl;
								cells[i][j].setrho_v(atof(line.c_str()));
							}
	
							//else cout << "#e: out of lines in file (readCells() in " << getFileName() << ")" << endl;
							k++;
						}
					}
				}
				if(line == field4){
				field4start = k;
				cout << "#i: e: separator on line " << k-1 << endl;
					for(j=1;j<npointsJ;j++){
						for(i=1;i<npointsI;i++){
							if(getline(file,line) && k >= field4start && k < (field4start + ncells + 1)){
								//cout << k << endl;
								cells[i][j].sete(atof(line.c_str()));
							}
	
							//else cout << "#e: out of lines in file (readCells() in " << getFileName() << ")" << endl;
							k++;
						}
					}
				}
			k++;
		}
	}
	else cout << "#e: file \"" << meshFile << "\" didn't open (readCells() in " << getFileName() << ")" << endl;
	file.close();
}
/*void setCellsPoints(){
	int i = 0;
	int j = 0;	
	double pc[4][2];
	for(i=0;i<npointsI;i++){
		for(j=0;j<npointsJ;j++){
			pc[0][0] = grid[i][j].getX();
			pc[0][1] = grid[i][j].getY();
			pc[1][0] = grid[i][j+1].getX();
			pc[1][1] = grid[i][j+1].getY();
			pc[2][0] = grid[i+1][j].getX();			
			pc[2][1] = grid[i+1][j].getY();
			pc[3][0] = grid[i+1][j+1].getX();
			pc[3][1] = grid[i+1][j+1].getY();
			cells[i][j].setPoints(pc);		
		}	
	}
}*/
void writeCellsFieldToCSV(string fileName){
	ofstream file;	
	file.open(fileName);
	file << "x,y,value" << endl;
	for(int i=0;i<npointsI+1;i++){
		for(int j=0;j<npointsJ+1;j++){
			file << i << "," << j << "," << cells[i][j].getrho() << endl;
		}	
	}
	file.close();
}
void submitVectorToCell(double* v,int i, int j)
{
	cells[i][j].setrho(v[0]);
	cells[i][j].setrho_u(v[1]);
	cells[i][j].setrho_v(v[2]);
	cells[i][j].sete(v[3]);
}
void writeResidium(string resFile,float res[4], int iter){
	ofstream file(resFile,std::ios::app);

	double p,ux,uy,rho_x,rho_y,rho;
	rho = res[0];
	rho_x = res[1];
	rho_y = res[2];
	ux = rho_x/rho;
	uy = rho_y/rho;
	p = (kappa-1.)*(res[3] - 0.5 * rho * ((ux * ux)+(uy * uy)));
	if(p<0.) p = p * (-1.0);
	file << iter << "," << rho_x << "," << rho_y << "," << p << "," << rho << "," << res[3] << endl;
}
void writeConfigurationReport(){
	string fileName = "0";
	
	time_t now = time(0);
	char* dt = ctime(&now);
	int iterations = (endTime - startTime) / timeStep;

//	fileName = "reports/report_eps" + to_string(eps) + "_iters" + to_string(iterations) + "_Ux" + initial_ux + "_Uy" + initial_uy + ".txt";
	fileName = "./" + reportName + "/report.txt";

	ofstream file;
	file.open(fileName);
	file << "---simulation report---" << endl;
	file << "date: " << dt << endl;	
	file << "case name: " << reportName << endl;
	file << endl;
	file << "---configuration---" << endl;
	file << "npointsI:" << npointsI << "; npointsJ:" << npointsJ << endl << "meshFile:" << meshFile << endl << "meshFileCSV:" << meshFileCSV << endl << "residualsFile: " << residualsFile << endl <<
	"initials: ux,uy,in_ux,in_uy,p,T,r,kappa:" << ux << ", " << uy << ", " << initial_ux << ", " << initial_uy << ", " << p << ", " << T << ", " << r << ", " << kappa << endl <<
	"timeStep: " << timeStep << ", startTime: " << startTime << ", endTime: " << endTime << ", iterations: " << iterations << endl << "writeInterval: " << writeInterval << ", residiumWriteInterval: " << resInterval << endl <<
	"eps: " << eps << endl;
	file << "---end---" << endl;
	file << endl;
	file.close();

}
void writeReport(double Cl, double Re,double runTime){
	string fileName;

//	fileName = "reports/report_eps" + eps + "_iters" + iterations + "_Ux" + initial_ux + "_Uy" + initial_uy + ".txt";
	fileName = "./" + reportName + "/report.txt";

	ofstream file(fileName,std::ios::app);

	file << "---results---" << endl;
	file << "Run time: " << runTime << " seconds" << endl;
	file << "Cl: " << Cl << endl;
	file << "Re: " << Re << endl;
}
void writeCl(double Cl,int iteration){
	string fileName;
	
	fileName = "./" + reportName + "/cls.csv";
	ofstream file(fileName,std::ios::app);
	file << iteration << "," << Cl << endl;

}
void writePressureOnWall(double pressure, double x){
	string fileName;

	fileName = "./" + reportName + "/wallPressure.csv";
	ofstream file(fileName,std::ios::app);
	file << x << "," << pressure << endl;
}
void printPressureOnWall(int iCellStart, int iCellEnd, int jWall){
	double pressure;
	double cp;
	double rho = p/(r*T);
	for(int i=iCellStart;i<=iCellEnd;i++){
		pressure = (cells[i][jWall].calc_p(kappa));
		cp = (pressure - p)/(0.5*rho*(ux*ux));
		cout << "cell " << i << "," << jWall << ", cp: " << cp << endl;
		//writePressureOnWall(pressure,absXCor);
	}
}
