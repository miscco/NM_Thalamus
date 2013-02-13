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
	vector<double> u_t1 = rand_inp(mtrand, res, T, onset, 5, 1E2, phi_st, 0, phi_inp);
	vector<double> u_t2 = rand_inp(mtrand, res, T, onset, 5, 1E2, phi_st, 0, phi_inp);

	// Initializing the populations;
	Thalamic_Colum Col(Connectivity);

	// setting up the data containers
	vector<double> Vt 		(T*res);
	vector<double> Vr 		(T*res);
	vector<double> Ca 		(T*res);
	vector<double> Phi_tt 	(T*res);
	vector<double> Phi_tr 	(T*res);
	vector<double> Phi_rt 	(T*res);
	vector<double> Phi_rr 	(T*res);
	vector<double> h_T_t	(T*res);
	vector<double> h_T_r	(T*res);
	vector<double> I_T_t	(T*res);
	vector<double> I_h		(T*res);

	int count = 0;

	// simulation
	for (int t=0; t<Time; ++t) {
		ODE (Col, u_t1[t], u_t2[t]);
		//ODE2(Col, u_t1[t]);
		if(t>=onset*res){
		get_data(count, Col, Vt, Vr, Ca, Phi_tt, Phi_tr, Phi_rt, Phi_rr, h_T_t, h_T_r, I_T_t, I_h);
		++count;
		}
	}

	plhs[0] = getMexArray(Vt);
	plhs[1] = getMexArray(Vr);
	plhs[2] = getMexArray(Ca);
	plhs[3] = getMexArray(Phi_tt);
	plhs[4] = getMexArray(Phi_tr);
	plhs[5] = getMexArray(Phi_rt);
	plhs[6] = getMexArray(Phi_rr);
	plhs[7] = getMexArray(h_T_t);
	plhs[8] = getMexArray(h_T_r);
	plhs[9] = getMexArray(I_T_t);
	plhs[10]= getMexArray(I_h);
	return;
}
