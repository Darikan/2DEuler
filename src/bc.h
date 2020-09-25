#pragma once

  //bc_type: 0 default, 1 freeStream, 2 outlet, 3 wall, 4 ami

class BC{
	private:
		int i;
		int j;
		int bc_type;
	public:
		BC();
		void setBC(int _i, int _j, int _bc_type);
		int getI();
		int getJ();
		int getBC_type();
};
