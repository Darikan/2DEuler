#include "cell.h"

Cell::Cell(){
	rho = 1.;
	rho_u = 1.;
	rho_v = 1.;
	e = 1.;
	bc = false;
}

void Cell::setValues(double _rho,double _rho_u, double _rho_v, double _e){
	rho = _rho;
	rho_u = _rho_u;
	rho_v = _rho_v;
	e = _e;
}

void Cell::setrho(double _rho){
	rho = _rho;
}

void Cell::setrho_u(double _rho_u){
	rho_u = _rho_u;
}

void Cell::setrho_v(double _rho_v){
	rho_v = _rho_v;
}

void Cell::sete(double _e){
	e = _e;
}
double Cell::getrho(){
	return rho;
}

double Cell::getrho_u(){
	return rho_u;
}

double Cell::getrho_v(){
	return rho_v;
}

double Cell::gete(){
	return e;
}

double Cell::calc_u(){
	if(rho == 0.){
		std::cout << "#e: zero rho (dividing by zero) in Cell::calc_u" << std::endl;
		return 0;
	}
	return rho_u / rho;
}

double Cell::calc_v(){
	if(rho == 0.){
		std::cout << "#e: zero rho (dividing by zero) in Cell::calc_v" << std::endl;
		return 0;
	}
	return rho_v / rho;
}

double Cell::calc_p(double kappa){
	double u = rho_u / rho;
	double v = rho_v / rho;
	return (kappa-1.)*(e-rho*(u * u + v * v)/2.);
}
