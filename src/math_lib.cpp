#include "math_lib.h"


M_vector addM_vectors(M_vector A, M_vector B){
	M_vector res;
	res.set(A.getX() + B.getX(),A.getY() + B.getY());
	return res;

}
double getCellWallArea(int iCell,int jCell, int k){
	Point p1;
	Point p2;
	double res = 0;
	if(k==0){
	/*p1.setX(grid[iCell-1][jCell-1].getX());
	p1.setY(grid[iCell-1][jCell-1].getY());
	p2.setX(grid[iCell][jCell-1].getX());
	p2.setY(grid[iCell][jCell-1].getX())
	*/
	p1.set(3.0,2.0);
	}
	//res = sqrt((p2.getX() - p1.getX()) * (p2.getX() - p1.getX()) + (p2.getY() - p1.getY()) * (p2.getY() - p1.getY()));
	if(res < .0) res = res * (-1.0);
	return res;
	
}
double getRectCellArea(int i, int j){
	double area = 1;
	double a = sqrt(((grid[i-1][j-1].getX() - grid[i-1][j].getX()) * (grid[i-1][j-1].getX() - grid[i-1][j].getX())) + 
		((grid[i-1][j-1].getY() - grid[i-1][j].getY()) * (grid[i-1][j-1].getY() - grid[i-1][j].getY())));
	double b = sqrt(((grid[i-1][j].getX() - grid[i][j].getX()) * (grid[i-1][j].getX() - grid[i][j].getX())) + 
		((grid[i-1][j].getY() - grid[i][j].getY()) * (grid[i-1][j].getY() - grid[i][j].getY())));
	area = a * b;
	return area;
}
double getCellArea(int iCell, int jCell){
	Point * p = new Point[4];
	double area = 1;
	p[0].set(grid[iCell-1][jCell-1].getX(),grid[iCell-1][jCell-1].getY());
	p[1].set(grid[iCell-1][jCell].getX(),grid[iCell-1][jCell].getY());
	p[2].set(grid[iCell][jCell].getX(),grid[iCell][jCell].getY());
	p[3].set(grid[iCell][jCell-1].getX(),grid[iCell][jCell-1].getY());
//	for(int i=0;i<4;i++) p[i].print();
//	std::cout << "ll: " << getLineLength(p[0],p[2]) << std::endl;
//	std::cout << "dpfl: " << getDistanceOfPointFromLine(p[3],p[0],p[2]) << std::endl;
//	std::cout << "dpfl2 p1: " << getDist(p[1].getX(),p[1].getY(),p[0].getX(),p[0].getY(),p[2].getX(),p[2].getY()) << std::endl;
//	std::cout << "dpfl2 p3: " << getDist(p[3].getX(),p[3].getY(),p[0].getX(),p[0].getY(),p[2].getX(),p[2].getY()) << std::endl;

	//area = 0.5 * getLineLength(p[0],p[2]) * (getDistanceOfPointFromLine(p[3],p[0],p[2]) + getDistanceOfPointFromLine(p[1],p[0],p[2]));
	area = 0.5 * getLineLength(p[0],p[2]) * (getDist(p[3].getX(),p[3].getY(),p[0].getX(),p[0].getY(),p[2].getX(),p[2].getY()) + getDist(p[1].getX(),p[1].getY(),p[0].getX(),p[0].getY(),p[2].getX(),p[2].getY()));
	delete[] p;
	return area;
}
double getLineLength(Point p1, Point p2){
	return sqrt( (p2.getX() - p1.getX()) * (p2.getX() - p1.getX()) + (p2.getY() - p1.getY()) * (p2.getY() - p1.getY()) );
}

void getLine(double x1, double y1, double x2, double y2, double &a, double &b, double &c)
{
//	std::cout << "getLine() coors: " << x1 << "," << y1 << "," << x2 << "," << y2 << std::endl;
	a = y1 - y2;
	b = x2 - x1;
	c = (x1-x2) * y1 + (y2-y1) * x1;
}
double getDist(double pct1X, double pct1Y, double pct2X, double pct2Y, double pct3X, double pct3Y)
{
	double a, b, c;
	getLine(pct2X, pct2Y, pct3X, pct3Y, a, b, c);
	
	a = pct2Y - pct3Y;
	b = pct3X - pct2X;
	c = pct2X * pct3Y - pct3X * pct2Y;
	//std::cout << "a,b,c" << a << "," << b << "," << c << std::endl;	
	double dist = (a * pct1X + b * pct1Y + c) / sqrt(a * a + b * b);
	if(dist<0.) dist = dist * (-1.);
//	std::cout << "dist in getDist(): " << dist << std::endl;
	return dist;
}
double getDistanceOfPointFromLine(Point p, Point A, Point B){ //not working
	double a,b,c,dist;
	a = A.getY() - B.getY();
	b = B.getX() - A.getX();
	c = A.getX() * B.getY() - B.getX() * A.getY();
	dist = (a * p.getX() + b * p.getY() + c) / sqrt(a * a + b * b);
	if(dist<0.) dist = dist * (-1.);
	return dist;

	//std::cout << "gll: " << getLineLength(a,b) << std::endl;	  
}
M_vector getForceOnWall(int iCell,int jCell,int side){
	int ia, ja, ib, jb;
	M_vector force_final;
	M_vector forceOnWall;
	double pressure;
	double cellForce;
	double wallLength;
	Point A;
	Point B;	

	switch(side){		//stejné indexování jako u BC_wall() v boundary.cpp
		case 0: 
			ia = 0;
			ja = 0;
			ib = 0;
			jb = 0;
			break;
		case 1:
			ia = 0;
			ja = 0;
			ib = 0;
			jb = 0;
			break;
		case 2:
			ia = 0;
			ja = 0;
			ib = 0;
			jb = 0;
			break;
		case 3:
			ia = 0;
			ja = 0;
			ib = 0;
			jb = 0;
			break;
	} 
//	A.set(grid[][].getX());
	pressure = cells[iCell][jCell].calc_p(kappa);
	wallLength = getWallLength(iCell,jCell,side);
//	M_vector wallNormal();
//	forceOnWall.set(,);

	cellForce = pressure * wallLength;
	return force_final;
}
double getLiftForceOnWall(int i,int jWall,int side){
	double wallXLength;
	Point A;
	Point B;	
	double xForce;
	double pressureOnWall;

	A.set(grid[i-1][jWall].getX(),grid[i-1][jWall].getY());
	B.set(grid[i][jWall].getX(),grid[i][jWall].getY());

	//TODO rework
	//wallLength = getLineLength(A,B);
	wallXLength = A.getX() - B.getX();
	if(wallXLength < 0.) wallXLength *= -1.;	
	pressureOnWall = cells[i][jWall].calc_p(kappa) - p;
	xForce = pressureOnWall * wallXLength;

	return xForce;
	
}
double getDragForceOnWall(int i,int jWall,int side){
	double wallYLength;
	Point A;
	Point B;	
	double yForce;
	double pressureOnWall;

	A.set(grid[i-1][jWall-1].getX(),grid[i-1][jWall-1].getY());
	B.set(grid[i-1][jWall].getX(),grid[i-1][jWall].getY());
	//wallLength = getLineLength(A,B);
	wallYLength = A.getY()-B.getY();	
	pressureOnWall = cells[i][jWall].calc_p(kappa) - p;
	yForce = pressureOnWall * wallYLength;

	return yForce;
	
}
double getWallLength(int i, int j,int side){
	Point p1;
	Point p2;
	p1.set(grid[i-1][j-1].getX(),grid[i-1][j-1].getY());
	p2.set(grid[i][j-1].getX(),grid[i][j-1].getY());
	return getLineLength(p1,p2);
}
M_vector integrateForceOnWall(int iCellStart,int iCellEnd, int jWall,int side){
	M_vector finalForce;
	M_vector dF;	
	
	for(int i=iCellStart;i<=iCellEnd;i++){
		dF.set(getDragForceOnWall(i,jWall,side),getLiftForceOnWall(i,jWall,side));
		finalForce = addM_vectors(finalForce,dF);
	}
	return finalForce;
}
Point getCenterOfCell(int iCell, int jCell){
	Point points[4];
	double xMax=0;
	double yMax=0;
	double xMin;
	double yMin;
	Point center;
	
	points[0].set(grid[iCell-1][jCell-1].getX(),grid[iCell-1][jCell-1].getY());
	points[1].set(grid[iCell-1][jCell].getX(),grid[iCell-1][jCell].getY());
	points[2].set(grid[iCell][jCell-1].getX(),grid[iCell][jCell-1].getY());
	points[3].set(grid[iCell][jCell].getX(),grid[iCell][jCell].getY());
	
	xMin = points[0].getX();
	yMin = points[0].getY();
	for(int i=0;i<4;i++){
		if(points[i].getX() > xMax) xMax = points[i].getX();
		if(points[i].getY() > yMax) yMax = points[i].getY();
		if(points[i].getX() < xMin) xMin = points[i].getX();
		if(points[i].getY() < yMin) yMin = points[i].getY();
	}
	center.set((xMax-xMin)/2.,(yMax-yMin)/2.);
	return center;
	
}
double integratePressureOnWall(int iCellStart,int iCellEnd, int jWall){
	double finalPressure = 0;
	for(int i=iCellStart;i<=iCellEnd;i++){
		//std::cout << "p on " << i << "," << jWall << ": " << cells[i][jWall].calc_p(kappa) << ", p diff: " << cells[i][jWall].calc_p(kappa) - p <<  std::endl;
		finalPressure += cells[i][jWall].calc_p(kappa) - p;
	}
	return finalPressure;
}

double calcDragCoefficient(){
	double density;
	double U;	
	double liftForce;
	double cd;
	Point A;
	Point B;
	double Aref;

	U = sqrt((initial_ux * initial_ux)+(initial_uy * initial_uy));
	density = p / (r * T);


//	TODO:top and bot points !!!	
	A.set(grid[24][34].getX(),grid[24][34].getY());
	B.set(grid[78][34].getX(),grid[78][34].getY());
	Aref = getLineLength(A,B);
	std::cout << "profile length: " << Aref << std::endl;
	liftForce = integrateForceOnWall(25,78,34,2).getX() - integrateForceOnWall(79,132,34,2).getX();
	cd = liftForce / (density * 0.5 * U * U * Aref);

	return cd;
}

double calcLiftCoefficient(){
	double density;
	double U;	
	double liftForce;
	double cl;
	Point A;
	Point B;
	double Aref;

	std::cout << "calculating lift coefficient" << std::endl;
	U = sqrt((initial_ux * initial_ux)+(initial_uy * initial_uy));
	density = p / (r * T);

	A.set(grid[24][34].getX(),grid[24][34].getY());
	B.set(grid[78][34].getX(),grid[78][34].getY());
	Aref = getLineLength(A,B);
	std::cout << "profile length: " << Aref << std::endl;
	liftForce = integrateForceOnWall(25,78,34,2).getY() - integrateForceOnWall(79,132,34,2).getY();
	cl = liftForce / (density * 0.5 * U * U * Aref);

	return cl;

}
double calcReynoldsNumber(){
	double Re;
	double U;
	double l;
	Point A;
	Point B;	
	const double viscosity = 1.5 * 0.00001; //20°C

	A.set(grid[24][34].getX(),grid[24][34].getY());
	B.set(grid[78][34].getX(),grid[78][34].getY());
	U = sqrt((initial_ux * initial_ux)+(initial_uy * initial_uy));
	l = getLineLength(A,B);
	Re = U * l / viscosity;

	return Re;
}
void _calcPressureOnWall(int iCellStart,int iCellEnd, int jWall){
	double pressure;
	double xOfCenter;
	double xSize;
	double xCellSize;
	double l;
	double step;
	double xCor;
	const int numberOfPoints = 50;
	Point A;
	Point B;
	int nOfPoints = 0;

	A.set(grid[24][34].getX(),grid[24][34].getY());
	B.set(grid[78][34].getX(),grid[78][34].getY());
	l = absVal(A.getX() - B.getX());
	xCor = A.getX();
	step = l / numberOfPoints;
	std::cout << "calculating pressure on wall with x step " << step << std::endl;
	std::cout << "l: " << l << ", A_x: " << A.getX() << std::endl;
	//TODO
	while(xCor <= A.getX() + l){
		for(int i=1;i<npointsI;i++){
			//for(int j=1;j<npointsJ;j++){
				if(grid[i-1][jWall].getX() <= xCor <= grid[i][jWall].getX()){
					writePressureOnWall(cells[i][jWall].calc_p(kappa),xCor);
					nOfPoints++;					
				}
			//}
		}
		xCor += step;
	}
	while(xCor <= A.getX() + l){
		for(int i=1;i<npointsI;i++){
			//if(grid[i-1][jWall]);
		}
	xCor += step;	
	}
	std::cout << "number of pressure points: " << nOfPoints << std::endl;
}
void calcPressureOnWall(int iCellStart,int iCellEnd, int jWall){
	double pressure;
	double absXCor = 0;
	double relXCor = 0;	
	double l;
	Point A;
	Point B;
	A.set(grid[24][34].getX(),grid[24][34].getY());
	B.set(grid[78][34].getX(),grid[78][34].getY());
	l = absVal(A.getX() - B.getX());

	for(int i=iCellStart;i<=iCellEnd;i++){
		pressure = (cells[i][jWall].calc_p(kappa) + cells[i+54][jWall].calc_p(kappa) - 2. * p);
//		absXCor = getCenterOfCell(i,jWall).getX();l
		absXCor = (grid[i][jWall].getX() - grid[i+1][jWall].getX())/2.;
		relXCor = (absXCor - A.getX());
		writePressureOnWall(pressure,absXCor);
	}
}
double absVal(double val){
	if(val < 0.) val *= -1.;
	return val;
}
float absFloat(double val){
	if(val < 0.) val *= -1.;
	return val;
}
