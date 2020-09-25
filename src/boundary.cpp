#include "boundary.h"

double scalarProduct(M_vector v1, M_vector v2){
	return v1.vx * v2.vx + v1.vy * v2.vy;
}


void loadInitialConditions(){
	std::cout << "initials: " << p << ", " << r << ", " << T << std::endl; 
	double inUx = initial_ux;
	double inUy = initial_uy;
	for(int i = 1;i<npointsI;i++){
		for(int j = 1;j<npointsJ;j++){
			cells[i][j].setrho(p/(r*T));
			cells[i][j].setrho_u(inUx*p/(r*T));			
			cells[i][j].setrho_v(inUy*p/(r*T));
			cells[i][j].sete((cells[i][j].getrho() * (inUx*inUx+inUy*inUy))/2. + p/(kappa-1.));
			}		
	}
}

void setBC_wall(int iStart,int iEnd, int jStart, int jEnd, int k){ //26,130,35,35        O->156 , 0->35
	M_vector u_nt(0,0);
	M_vector u_xy(0,0);
	int ia, ja, ib, jb, wall_i, wall_j;
	double wall_ux = 0;
	double wall_uy = 0;
	double ux_s,uy_s,rho;	
	for(int i = iStart;i<=iEnd;i++){
		for(int j = jStart;j<=jEnd;j++){
			switch(k){
				case 0: 
					ia = i - 1;
					ja = j;
					ib = i;
					jb = j;
					wall_i =  0;
					wall_j =  1;
					break;
				case 1: 
					ia = i - 1 ;
					ja = j - 1;
					ib = i - 1;
					jb = j;
					wall_i =  -1;
					wall_j =  0;
					break;
				case 2: 
					ia = i;
					ja = j - 1;
					ib = i - 1;
					jb = j - 1;
					wall_i =  0;
					wall_j =  -1;
					break;
				case 3: 
					ia = i;
					ja = j;
					ib = i;
					jb = j - 1;
					wall_i =  1;
					wall_j =  0;
					break;
			}
			if(cells[i][j].getrho() != 0){
				wall_ux = cells[i][j].calc_u();
				wall_uy = cells[i][j].calc_v();
			}
			else {
				wall_ux = 0;
				wall_uy = 0;
			}				
			M_vector u_wall(wall_ux,wall_uy);
			//M_vector t(grid[i+1][j-1].getX() - grid[i][j-1].getX(), grid[i+1][j-1].getY() - grid[i][j-1].getY());
			//std::cout << "grid on " << ia << ", " << ja << "; " << ib << ", " << jb << std::endl;
			M_vector t(grid[ib][jb].getX() - grid[ia][ja].getX(), grid[ib][jb].getY() - grid[ia][ja].getY());		
			//M_vector t(0,0);			
		//	t.print();
			M_vector n = t.getPerpendicularVector();
			n.normalize();
		//	n.print();			
			M_vector vn(scalarProduct(u_wall,n)*n.vx,scalarProduct(u_wall,n)*n.vy);
			ux_s = wall_ux - 2.*vn.vx;
			uy_s = wall_uy - 2.*vn.vy;
			rho = cells[i][j].getrho();
			//std::cout << "wall_ux: " << wall_ux << ", wall_uy: " << wall_uy << ", ux_s: " << ux_s << ", uy_s: " << uy_s << ", shadow cell: " << i+wall_i << ", " << j+wall_j << ", current cell: " << i << ", " << j << std::endl; 
			cells[i+wall_i][j+wall_j].setrho(rho);
			cells[i+wall_i][j+wall_j].setrho_u(ux_s*rho);
			cells[i+wall_i][j+wall_j].setrho_v(uy_s*rho);
//			cells[i+wall_i][j+wall_j].setrho_v(cells[i][j].getrho_v());
//			cells[i+wall_i][j+wall_j].setrho_u(0.);
			cells[i+wall_i][j+wall_j].sete(rho * (ux_s*ux_s+uy_s*uy_s)/2. + p/(kappa-1.));
			cells[i+wall_i][j+wall_j].bc = true;
			//std::cout << "new wall u: " << cells[i+wall_i][j+wall_j].calc_u() << ", new wall v: " << cells[i+wall_i][j+wall_j].calc_v() << 
			//", cell u: " << cells[i][j].calc_u() << ", cell v: " << cells[i][j].calc_v() << std::endl;
			BC boundary;
			boundary.setBC(i,j,3);
			bc.push_back(boundary);
		}	
	}
}

void setBC_ami(int iStart,int iEnd, int jStart, int jEnd){  //131,156,35,35
	for(int i = iStart;i<=iEnd;i++){
		for(int j = jStart;j<=jEnd;j++){
			//cout << "i,j: " << i << "," << j << endl;
			cells[i][j].setrho(cells[npointsI-i][j-1].getrho());
			cells[i][j].setrho_u(cells[npointsI-i][j-1].getrho_u());
			cells[i][j].setrho_v(cells[npointsI-i][j-1].getrho_v());
			cells[i][j].sete(cells[npointsI-i][j-1].gete());
			cells[i][j].bc = true;
			BC boundary;
			boundary.setBC(i,j,4);
			bc.push_back(boundary);
		}	
	}
}

void setBC_freeStream(int iStart,int iEnd, int jStart, int jEnd){
	for(int i = iStart;i<=iEnd;i++){
		for(int j = jStart;j<=jEnd;j++){
			
			cells[i][j].setrho(p/(r*T));
			cells[i][j].setrho_u(ux*p/(r*T));
			cells[i][j].setrho_v(uy*p/(r*T));
			cells[i][j].sete((p/(r*T)) * (ux*ux+uy*uy)/2. + p/(kappa-1.));
			cells[i][j].bc = true;	
			BC boundary;
			boundary.setBC(i,j,1);
			bc.push_back(boundary);
		}	
	}
}

void setBC_outlet(int iStart, int iEnd, int jStart, int jEnd,int side){	//155,155,0,35
	for(int i = iStart;i<=iEnd;i++){
		for(int j = jStart;j<=jEnd;j++){
			//cout << "outlet:"<<cells[i+side][j].getrho() << ",";
			cells[i][j].setrho(cells[i+side][j].getrho());  //154,0->35
			cells[i][j].setrho_u(cells[i+side][j].getrho_u());
			cells[i][j].setrho_v(cells[i+side][j].getrho_v());
			cells[i][j].sete(cells[i+side][j].gete());
			cells[i][j].bc = true;
			BC boundary;
			boundary.setBC(i,j,2);
			bc.push_back(boundary);
		}	
	}
	
}
void printBC_field(){
	std::cout << bc.size() << " cells with boundary condition" << std::endl;
	for(int i=0;i<bc.size();i++){
		std::cout << bc[i].getI() << ", " << bc[i].getJ() << ", " <<bc[i].getBC_type() << std::endl;
	}
}
void writeBoundaryToCSV(std::string filename){   // 0 default, 1 freeStream, 2 outlet, 3 wall, 4 ami
	std::ofstream file;
	file.open(filename);
	file << "x,y,bc_type" << std::endl;    
	for(int i=0;i<bc.size();i++){
		file << bc[i].getI() << "," << bc[i].getJ() << "," << bc[i].getBC_type() << std::endl;
	}
	file.close();
}
void setBoundary(){
//	int bc_iCell = npointsI;
//	int bc_jCell = npointsJ;
/*
	setBC_freeStream(0,0,1,bc_jCell);
	setBC_outlet(bc_iCell,bc_iCell,1,bc_jCell,-1);
//	setBC_freeStream(bc_iCell,bc_iCell,1,bc_jCell);
	setBC_wall(1,bc_iCell-1,1,1,2);
	setBC_wall(1,bc_iCell-1,bc_jCell-1,bc_jCell-1,0);
*/


	setBC_freeStream(0,156,0,0);
	setBC_outlet(0,0,0,35,1);
	setBC_outlet(156,156,0,35,-1);
	setBC_ami(0,24,35,35);
	setBC_ami(133,156,35,35);
	setBC_wall(25,132,34,34,0);

/*

	setBC_freeStream(0,0,1,bc_jCell-1);
	setBC_freeStream(bc_iCell,bc_iCell,1,bc_jCell-1);
	setBC_freeStream(1,bc_iCell-1,0,0);
	setBC_freeStream(1,bc_iCell-1,bc_jCell,bc_jCell);
*/
/*
	setBC_freeStream(0,0,1,3);
	setBC_freeStream(4,4,1,3);
	setBC_freeStream(1,3,0,0);
	setBC_freeStream(1,3,4,4);

*/

}
