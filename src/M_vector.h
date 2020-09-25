#ifndef M_VECTOR
#define M_VECTOR

#include <cmath>
#include <iostream>

class M_vector{
	public:
		double vx;
		double vy;
		M_vector(double _vx, double _vy);
		M_vector();	
		double getX();
		double getY();
		double set(double _vx, double _vy);
		double getSize();
		void normalize();
		M_vector getPerpendicularVector();
		void print();
		void multiply(double a);
};

#endif
