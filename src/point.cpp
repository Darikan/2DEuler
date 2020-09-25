#include "point.h"

Point::Point(){
	x = 0;
	y = 0;
}

Point::Point(double ix,double iy){
	x = ix;
	y = iy;
}

double Point::getX(){
	return x;
}

double Point::getY(){
	return y;
}

void Point::setX(double ix){
	x = ix;
}

void Point::setY(double iy){
	y = iy;
}

void Point::set(double ix,double iy){
	x = ix;
	y = iy;
}
void Point::print(){
	std::cout << "( " << x << "; " << y << " )" << std::endl;
}

