/*****************************************************************************************************/
/**********************************		file for code verification	**********************************/
/*****************************************************************************************************/
#include <iostream>
#include <ctime>
#include <vector>
#include "randoms.h"
#include "Thalamic_Column.h"
#include "ODE.h"

using std::vector;

extern const int T 		= 50;
extern const int onset	= 5;
extern const int res 	= 1E4;
extern const double dt 	= 1E3/res;
extern const double h	= sqrt(dt);

// simulation of the thalamic model
int main(void) {
	// Initializing the mersenne twister.
	MTRand mtrand;
	const int Time 			= (T+onset)*res;

	// random input
	vector<double> u_t1 = rand_var(mtrand, (T+onset)*res, mphi_st, dphi_st);
	vector<double> u_t2 = rand_var(mtrand, (T+onset)*res, mphi_st, dphi_st);

	// Initializing the populations;
	Thalamic_Column Col;

	// takes the time of the simulation
	time_t start,end;
	time (&start);

	// simulation
	for (int t=0; t< T*res; ++t) {
		ODE (Col, u_t1[t], u_t2[t]);
		//ODE2(Col, u_t1[t]);
	}
	time (&end);

	// time consumed by the simulation
	double dif = difftime(end,start);
	std::cout << "simulation done!\n";
	std::cout << "took " << dif 	<< " seconds" << "\n";
	std::cout << "end\n";
}
