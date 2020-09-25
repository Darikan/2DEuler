#pragma once

#include <iostream>
class Point{
	private:
		double x;
		double y;
		
	public:
		Point();
		Point(double ix,double iy);
		double getX();
		double getY();
		void setX(double ix);
		void setY(double iy);
		void set(double ix,double iy);
		void print();
};
