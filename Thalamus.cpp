/****************************************************************************************************/
/* 		Implementation of the simulation as MATLAB routine (mex compiler)							*/
/* 		mex command is given by:																	*/
/* 		mex CXXFLAGS="\$CXXFLAGS -std=gnu++0x -fpermissive" Thalamus.cpp Thalamic_Column.cpp		*/
/*		The Simulation requires the following boost libraries:	Preprocessor						*/
/*																Random								*/
/****************************************************************************************************/
#include <ctime>
#include "mex.h"
#include "matrix.h"
#include "Thalamic_Column.h"
#include "Stimulation.h"
#include "saves.h"
#include "ODE.h"

/****************************************************************************************************/
/*										Fixed simulation settings									*/
/****************************************************************************************************/
extern const int onset	= 5;								// time until data is stored in  s
extern const int res 	= 1E4;								// number of iteration steps per s
extern const int red 	= res/100;							// number of iterations that is saved
extern const double dt 	= 1E3/res;							// duration of a timestep in ms
extern const double h	= sqrt(dt);							// squareroot of dt for SRK iteration
/****************************************************************************************************/
/*										 		end			 										*/
/****************************************************************************************************/


/****************************************************************************************************/
/*										Simulation routine	 										*/
/*										lhs defines outputs											*/
/*										rhs defines inputs											*/
/****************************************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	// Initializing the seeder.
	srand(time(NULL));

	// Fetch inputs
	const int T				= (int) (mxGetScalar(prhs[0]));	// duration of simulation in s
	const int Time 			= (T+onset)*res;				// total number of iteration steps
	double* Param_Thalamus	= mxGetPr (prhs[1]);			// parameters of thalamic module
	double* var_stim	 	= mxGetPr (prhs[2]);			// parameters of stimulation protocol

	// Initializing the populations;
	Thalamic_Column Thalamus(Param_Thalamus);

	// Initialize the stimulation protocol
	Stim	Stimulation(Thalamus, var_stim);

	// setting up the data containers
	mxArray* Vt		= SetMexArray(1, T*res/red);
	mxArray* Vr		= SetMexArray(1, T*res/red);

	// Pointer to the actual data block
	double* Pr_Vt	= mxGetPr(Vt);
	double* Pr_Vr	= mxGetPr(Vr);

	// simulation
	int count = 0;
	for (int t=0; t<Time; ++t) {
		ODE (Thalamus);
		Stimulation.check_stim(t);
		if(t>=onset*res && t%red==0){
			get_data(count, Thalamus, Pr_Vt, Pr_Vr);
			++count;
		}
	}

	// output of the simulation
	plhs[0] = Vt;
	plhs[1] = Vr;
return;
}
/****************************************************************************************************/
/*												end													*/
/****************************************************************************************************/
