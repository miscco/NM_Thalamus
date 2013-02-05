#include <ctime>
#include <vector>
#include "mex.h"
#include "matrix.h"
#include "randoms.h"
#include "Thalamic_Colum.h"
#include "saves.h"
#include "ODE.h"
using std::vector;

// Implementation of the main file for mex compiler
// mex command is given by:
// mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" SteynRoss.cpp Thalamic_Colum.cpp

extern const int res 	= 1E3;
extern const double dt 	= 1E3/res;
extern const double h	= sqrt(dt);


// simulation of the model proposed in Steyn-Ross2004

// input arguments are a vector of length 8 with the connectivities and an integer setting the resolution of the grid
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	// Initializing the mersenne twister.
	MTRand mtrand;

	// inputs
	double* Connectivity 	= mxGetPr (prhs[0]);
	const int T				= (int)(mxGetScalar(prhs[1]));
	const int onset			= (int)(mxGetScalar(prhs[2]));

	const int Time 	= (T+onset)*res;

	// creating the random input
	vector<double> u_e1 = rand_inp(mtrand, res, T, onset, 10, 1E3, phi_st, phi_st, phi_inp);
	vector<double> u_e2 = rand_inp(mtrand, res, T, onset, 10, 1E3, phi_st, phi_st, phi_inp);
	vector<double> u_i1 = rand_inp(mtrand, res, T, onset, 10, 1E3, phi_st, phi_st, phi_inp);
	vector<double> u_i2 = rand_inp(mtrand, res, T, onset, 10, 1E3, phi_st, phi_st, phi_inp);

	// Initializing the populations;
	Thalamic_Colum Col(Connectivity);

	// setting up the data containers
	vector<double> Ve 		(T*res);
	vector<double> Vi 		(T*res);
	vector<double> Phi_ee 	(T*res);
	vector<double> Phi_ei 	(T*res);
	vector<double> Phi_ie 	(T*res);
	vector<double> Phi_ii 	(T*res);
	vector<double> I_T		(T*res);

	int count = 0;

	// simulation
	for (int t=0; t<Time; ++t) {
		ODE (Col, u_e1[t], u_e2[t], u_i1[t], u_i2[t]);
		//ODE2(Col, u_e1[t], u_i1[t]);
		if(t>=onset*res){
		get_data(count, Col, Ve, Vi, Phi_ee, Phi_ei, Phi_ie, Phi_ii, I_T);
		++count;
		}
	}

	plhs[0] = getMexArray(Ve);
	plhs[1] = getMexArray(Vi);
	plhs[2] = getMexArray(Phi_ee);
	plhs[3] = getMexArray(Phi_ei);
	plhs[4] = getMexArray(Phi_ie);
	plhs[5] = getMexArray(Phi_ii);
	plhs[6] = getMexArray(I_T);
	return;
}
