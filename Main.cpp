#include <iostream>
#include <ctime>
#include <vector>
#include "matio.h"

#include "randoms.h"
#include "Thalamic_Colum.h"
#include "ODE.h"

using std::vector;

extern const int T 		= 120;
extern const int res 	= 1E3;
extern const double dt 	= 1E3/res;
extern const double h	= sqrt(dt);


// simulation of the model proposed in Steyn-Ross2009

int main(void) {
	// Initializing the mersenne twister.
	MTRand mtrand;

	// creating the random input
	vector<double> u_t1 = rand_inp(mtrand, res, T, 0, 10, 1E3, phi_st, phi_st, phi_inp);
	vector<double> u_t2 = rand_inp(mtrand, res, T, 0, 10, 1E3, phi_st, phi_st, phi_inp);

	// Initializing the populations;
	Thalamic_Colum Col;

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
