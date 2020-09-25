#include "M_vector.h"

M_vector::M_vector(double _vx, double _vy){
	
	vx = _vx;
	vy = _vy;
}
M_vector::M_vector(){
	
	vx = 0.;
	vy = 0.;
}
double M_vector::getX(){
	return vx;
}
double M_vector::getY(){
	return vy;
}

double M_vector::getSize(){
	return sqrt((vx*vx)+(vy*vy));
}

double M_vector::set(double _vx, double _vy){
	vx = _vx;
	vy = _vy;
}

void M_vector::normalize(){
	double size = 1.;	
	size = getSize();
	vx = vx / size;
	vy = vy / size;
}

M_vector M_vector::getPerpendicularVector(){
	M_vector perp(vy,-vx);
	return perp;
}

void M_vector::print(){
	std::cout << "(" << vx << ", " << vy << ")" << std::endl; 
}

void M_vector::multiply(double a){
	vx = vx * a;
	vy = vy * a;
}

