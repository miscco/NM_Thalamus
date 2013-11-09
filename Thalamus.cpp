/*****************************************************************************************************/
/******************************	main file for mex file generation	**********************************/
/*****************************************************************************************************/
#include <vector>
#include "mex.h"
#include "matrix.h"
#include "randoms.h"
#include "Thalamic_Column.h"
#include "saves.h"
#include "ODE.h"

using std::vector;

extern const int res 	= 1E4;
extern const double dt 	= 1E3/res;
extern const double h	= sqrt(dt);

// input arguments are a vector of length 8 with the connectivities and an integer setting the resolution of the grid
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	// Initializing the mersenne twister.
	MTRand mtrand;

	// inputs
	double* Connectivity 	= mxGetPr (prhs[0]);
	const int T				= (int)(mxGetScalar(prhs[1]));
	const int onset			= (int)(mxGetScalar(prhs[2]));
	double* var_stim	 	= mxGetPr (prhs[3]);

	const int Time 			= (T+onset)*res;

	// random input
	vector<double> u_t1 = rand_var(mtrand, (T+onset)*res, phi_st, phi_st);
	vector<double> u_t2 = rand_var(mtrand, (T+onset)*res, phi_st, phi_st);

	// random input with phase independent stimulation
	//vector<double> u_t1 = rand_inp(mtrand, Time, mphi_st, dphi_st, onset, var_stim);
	//vector<double> u_t2 = rand_inp(mtrand, Time, mphi_st, dphi_st, onset, var_stim);


	// Initializing the populations;
	Thalamic_Column Col(Connectivity);

	// setting up the data containers
	vector<double> Vt 		(T*res);
	vector<double> Vr 		(T*res);
	vector<double> Cat	 	(T*res);
	vector<double> Car	 	(T*res);
	vector<double> Phi_tr 	(T*res);
	vector<double> Phi_rt	(T*res);
	vector<double> I_T_t	(T*res);
	vector<double> I_T_r	(T*res);
	vector<double> I_KCa	(T*res);
	vector<double> I_CAN	(T*res);
	vector<double> I_h		(T*res);

	int count = 0;
	for (int t=0; t<Time; ++t) {
		ODE (Col, u_t1[t], u_t2[t]);
		if(t>=onset*res){
			get_data(count, Col, Vt, Vr, Cat, Car, Phi_tr, Phi_rt, I_T_t, I_T_r, I_KCa, I_CAN, I_h);
			++count;
		}
	}

	// output of the simulation
	plhs[0] = getMexArray(Vt);
	plhs[1] = getMexArray(Vr);
	plhs[2] = getMexArray(Cat);
	plhs[3] = getMexArray(Car);
	plhs[4] = getMexArray(Phi_tr);
	plhs[5] = getMexArray(Phi_rt);
	plhs[6] = getMexArray(I_T_t);
	plhs[7] = getMexArray(I_T_r);
	plhs[8] = getMexArray(I_KCa);
	plhs[9] = getMexArray(I_CAN);
	plhs[10]= getMexArray(I_h);
return;
}
