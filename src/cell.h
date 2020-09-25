#ifndef CELL_H
#define CELL_H

#include "point.h"
#include <iostream>

class Cell{
	private:
		double rho,rho_u,rho_v,e;
		int i;
	public:
		bool bc;
		Cell();
		void setValues(double _rho,double _rho_u, double _rho_v, double _e);
		void setrho(double _rho);
		void setrho_u(double _rho_u);
		void setrho_v(double _rho_v);
		void sete(double _e);
		double getrho();
		double getrho_u();
		double getrho_v();
		double gete();
		double calc_u();
		double calc_v();
		double calc_p(double kappa);
};

#endif
