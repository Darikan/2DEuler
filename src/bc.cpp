#include "bc.h"

  //bc_type: 0 default, 1 freeStream, 2 outlet, 3 wall, 4 ami

BC::BC(){
	i = 0;
	j = 0;
	bc_type = 0;
}
void BC::setBC(int _i, int _j, int _bc_type){
	i = _i;
	j = _j;
	bc_type = _bc_type;
}
int BC::getI(){
	return i;
}
int BC::getJ(){
	return j;
}
int BC::getBC_type(){
	return bc_type;
}

