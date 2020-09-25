#include "LFscheme.h"

using namespace std;

void printVector(std::string name,double * v,int size){
//	v = new double[size];
	cout << name << " ( ";
	for(int i =0;i<size;i++){
		cout << v[i] << " ";
	}
	cout << ")" << endl;
}
void increaseVector(double* v1, double* v2){
	for(int i = 0;i<4;i++) v1[i] = v1[i] + v2[i];
}

double * addVectors(double* v1, double* v2){
	double * res = new double[4];
	for(int i = 0;i<4;i++) res[i] = v1[i] + v2[i];
	return res;
}
double * substractVectors(double* v1, double* v2){
	double * res = new double[4];
	for(int i = 0;i<4;i++) res[i] = v1[i] - v2[i];
	return res;
}

double * multiplyVector(double a, double* v1){
	double * res = new double[4];
	for(int i = 0;i<4;i++) res[i] = v1[i] * a;
	return res;
}
void residUpdate(float resid[4], int iter){
	for(int i=0;i<4;i++){
		resid[i] = abs(resid[i]);
	}
	if(true) cout << "writing residium" << endl;
	string fileName = "./" + reportName + "/residuals.csv";
	writeResidium(fileName,resid,iter);
}	
double * totalFlux(int iCell, int jCell,double cellArea, double dt, double * W,bool debug){
	double * flux = new double[4];
	double * eps_flux = new double[4];
	double * LF_flux;
	double Wk[4];
	int ikCell,jkCell;
	M_vector nk(0,0);
	M_vector u_nt(0,0);
	double wallArea = 0;
	double uk;
	double vk;
	double density;
	double pressure;
	double Fp[4];
	double Gp[4];
	double Fk[4];
	double Gk[4];
	double * fiX;
	double * fiY;
	int iTest = 1;
	int jTest = 1;
	int ia,ja,ib,jb;
	

	for(int i=0;i<4;i++) {flux[i] = 0; eps_flux[i] = 0;}
	uk = cells[iCell][jCell].calc_u();
	vk = cells[iCell][jCell].calc_v();
	density = cells[iCell][jCell].getrho();
	pressure = (kappa-1.)*(cells[iCell][jCell].gete() - 0.5 * density * ((uk * uk)+(vk * vk)));

	Fp[0] = density * uk;
	Fp[1] = density * uk * uk + pressure;
	Fp[2] = density * uk * vk;
	Fp[3] = uk * (cells[iCell][jCell].gete() + pressure);

	Gp[0] = density * vk;
	Gp[1] = density * vk * uk;
	Gp[2] = density * vk * vk + pressure;
	Gp[3] = vk * (cells[iCell][jCell].gete() + pressure);
	
	if(debug){
		cout << endl;
		cout << "pressure: " << pressure << ", density: " << density << endl;
		cout << "uk: " << uk << " e: " << cells[iCell][jCell].gete() << endl;
		if(iCell == iTest && jCell == jTest && true){
			cout << "Fluxes: " << endl;	
			printVector("Fp",Fp,4);
			printVector("Gp",Gp,4);
		}
	}

	for(int k=0;k<4;k++){
		if(debug){		
			cout << endl;
			cout << "k: " << k << " ";
			cout << "pressure: " << pressure << ", density: " << density << endl;
		}
		switch(k){
			case 0: 
				ikCell = iCell; jkCell=jCell+1;
				ia = iCell - 1;
				ja = jCell;
				ib = iCell;
				jb = jCell;
				break;
			case 1: 
				ikCell = iCell - 1; jkCell=jCell;
				ia = iCell - 1;
				ja = jCell - 1;
				ib = iCell - 1;
				jb = jCell;
				break;
			case 2: 
				ikCell = iCell; jkCell=jCell-1;
				ia = iCell;
				ja = jCell - 1;
				ib = iCell - 1;
				jb = jCell - 1;
				break;
			case 3: 
				ikCell = iCell + 1; jkCell=jCell;
				ia = iCell;
				ja = jCell;
				ib = iCell;
				jb = jCell - 1;
				break;
		}
		uk = cells[ikCell][jkCell].calc_u();
		vk = cells[ikCell][jkCell].calc_v();
		density = cells[ikCell][jkCell].getrho();
		pressure = (kappa-1.)*(cells[ikCell][jkCell].gete() - 0.5 * density * ((uk * uk)+(vk * vk)));
		if(debug){
			cout << "ikCell: " << ikCell << ", jkCell: " << jkCell << ",uk: " << uk << ",vk: " << vk << endl;
			cout << "e: " << cells[ikCell][jkCell].gete() + pressure << endl;
		}				
		Fk[0] = density * uk;
		Fk[1] = density * uk * uk + pressure;
		Fk[2] = density * uk * vk;
		Fk[3] = uk * (cells[ikCell][jkCell].gete() + pressure);
	
		Gk[0] = density * vk;
		Gk[1] = density * vk * uk;
		Gk[2] = density * vk * vk + pressure;
		Gk[3] = vk * (cells[ikCell][jkCell].gete() + pressure);	
	
		Wk[0] = density;
		Wk[1] = density * uk;
		Wk[2] = density * vk;
		Wk[3] = cells[ikCell][jkCell].gete();
		M_vector t(grid[ib][jb].getX() - grid[ia][ja].getX(), grid[ib][jb].getY() - grid[ia][ja].getY());

		//M_vector t(1,1);
		//M_vector t(0,0);	
		nk = t.getPerpendicularVector();
		nk.normalize();
		wallArea = t.getSize();
		
		double * fiX_a;
		double * fiY_a;
		double * flux_a;
		double * flux_n;
		double * eps_flux_s;
		double * eps_flux_m;
		//printVector("(add)",addVectors(Fk,Fp),4);
		
		fiX_a = addVectors(Fk,Fp);
		fiX = multiplyVector(0.5 * nk.vx,fiX_a);
		fiY_a = addVectors(Gk,Gp);
		fiY = multiplyVector(0.5 * nk.vy,fiY_a);
		flux_a = addVectors(fiX,fiY);
		flux_n = multiplyVector(wallArea,flux_a);


		increaseVector(flux,flux_n);
		
		//printVector("flux",flux,4);
		delete[] flux_n;
		delete[] fiX_a;
		delete[] fiY_a;
		delete[] flux_a;
		eps_flux_s = substractVectors(Wk,W);
		eps_flux_m = multiplyVector(eps*cellArea/(4.*dt),eps_flux_s);
		increaseVector(eps_flux,eps_flux_m);
		//eps_flux = addVectors(eps_flux,multiplyVector(eps*cellArea/(4.*dt),substractVectors(Wk,W)));
		delete[] eps_flux_s;
		delete[] eps_flux_m;
		if(debug && iCell == iTest && jCell == jTest){
			cout << "nkx, nky: " << nk.vx << ", " << nk.vy << " tx, ty: " << t.vx << ", " << t.vy << " wall size: " << wallArea << endl;
			printVector("flux",flux,4);
			cout << " "; 
			printVector("eps_flux", eps_flux, 4);
			cout << endl;
			printVector("fiX",fiX,4);
			printVector("fiY",fiY,4);
			printVector("Fk",Fk,4);
			printVector("Gk",Gk,4);
			printVector("Wk",Wk,4);
			cout << endl;
		}

		delete[] fiX;
		delete[] fiY;
	}
	LF_flux = substractVectors(flux,eps_flux);
	if(debug){	
		printVector("final flux from neighbors",flux,4);
		printVector("final LF_flux for this cell",LF_flux,4);
//		printVector("final LF_flux for this cell",LF_flux,4);
	}
	
	//if((iCell*jCell)%4000 == 0) printVector("Fp",Fp,4);
	//if((iCell*jCell)%4000 == 0) printVector("Gp",Gp,4);
	//if(iCell == 4 && jCell == 4) printVector("Gp",Gp,4);

	delete[] flux;
	delete[] eps_flux;
	//delete[] W;
	//printVector("Total LF_flux: ",LF_flux,4);
	return LF_flux;

	//TODO: delete[] flux;
}

void runCalculation(bool debug){
	double t = startTime;
	double dt = timeStep;
	double cellArea = 1.;
	int i,j;
	int iter = 1;
	int it = 0;
	double * Wn;
	float resid[4] = {0,0,0,0};
	//double * W = new double[4];
	int c = 0;
	//double * LF_flux = new double[4];
	//cout << "#i: " << cells[1][4].getrho() << endl;
	//int endIter = 100;
//	cellArea = 0.0004;
	while(t<=endTime){
		cout << "-------------------------" << endl;
		cout << "time " << t << endl;
		cout << "iteration: " << iter << endl;
//		-------------------------------------------------------------------------------------------
		for(i=1;i<npointsI;i++){
			for(j=1;j<npointsJ;j++){
				double * W = new double[4];
				cellArea = getCellArea(i,j);
				if(debug) {cout << "cell area on " << i << ", " << j << ": " << cellArea << endl;}
				W[0] = cells[i][j].getrho();
				W[1] = cells[i][j].getrho_u();
				W[2] = cells[i][j].getrho_v();
				W[3] = cells[i][j].gete();


				if(debug){
					cout << "#i: values in cell [" << i << "," << j << "]" << endl;
					printVector("W",W,4);
					cout << "cell area: " << cellArea << endl;
				}
				//flux = totalFlux(i,j,cellArea,dt,W);	
				double * Wnn;
				double * totalFlux_return;
				totalFlux_return = totalFlux(i,j,cellArea,dt,W,debug);
				Wnn = multiplyVector((dt/cellArea), totalFlux_return);
				Wn = substractVectors(W,Wnn);
				delete[] Wnn;
				delete[] totalFlux_return;					

				submitVectorToCell(Wn,i,j);

				for(int r=0;r<4;r++) {
					resid[r] = resid[r] + absVal(Wn[r] - W[r]);
				}				

				if(false){
					cout << "#i: values in cell [" << i << "," << j << "]" << endl;
					printVector("Wn",Wn,4);
				}
				c++;
				delete[] Wn;
				delete[] W;
				}
//			----------------------------------------------------------------------------------------

			
			}
		for(int r=0;r<4;r++) {
			resid[r] = resid[r]/ncells;
		}	
			//cout << "c: " << c << endl;
		c=0;
		it = iter;
		if(iter % writeInterval == 0) {
			std::cout << "writing mesh, time: " << t << ", iteration: " << it << std::endl; 		
			writeMesh(meshFile,false,0);
			}
		if(iter % resInterval == 0) {
			cout << resid[1] << endl;		
			residUpdate(resid,iter);
			double cl = calcLiftCoefficient();
			writeCl(cl,iter);
		}
		t = t + dt;
		iter++;	
		cout << endl; 
		for(int r=0;r<4;r++) resid[r] = 0;		
		setBoundary();	

	}

	cout << "DONE!" << endl;
	cout << iter - 1 << " iterations" << endl;
}
void testFields(){


	for(int i=0;i<npointsI;i++){
		delete[] grid[i];
	}
	delete[] grid;
	for(int i=0;i<npointsI+1;i++){
		delete[] cells[i];
	}
	delete[] cells;
}

