#include <iostream>
#include <ctime>
#include <vector>
#include "randoms.h"
#include "matio.h"

#include "Cortical_Colum.h"

#include "saves.cpp"
#include "ODE.cpp"

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
	vector<double> u_e1 = rand_var(T*res, mtrand, 0, 1500);
	vector<double> u_e2 = rand_var(T*res, mtrand, 0, 1500);
	vector<double> u_i1 = rand_var(T*res, mtrand, 0, 750);
	vector<double> u_i2 = rand_var(T*res, mtrand, 0, 750);

	// Initializing the populations;
	Cortical_Colum Col;

	// setting up the data containers
	vector<double> Ve (T*res);
	vector<double> Vi (T*res);


	// takes the time of the simulation
	time_t start,end;
	time (&start);

	// simulation
	for (int t=0; t< T*res; ++t) {
		ODE (Col, u_e1[t], u_e2[t], u_i1[t], u_i2[t]);
		//ODE2(Col, u_e1[t], u_i1[t]);
		get_data(t, Col, Ve, Vi);
	}

	time (&end);
	// time consumed by the simulation
	double dif = difftime(end,start);
	std::cout << "simulation done!\n";
	std::cout << "took " << dif 	<< " seconds" << "\n";

	_SAVEVARS((Ve)(Vi))
	std::cout << "end\n";
}
