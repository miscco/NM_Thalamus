/*****************************************************************************************************/
/******************************	main file for mex file generation	**********************************/
/*****************************************************************************************************/
#include <vector>
#include "mex.h"
#include "matrix.h"
#include "Thalamic_Column.h"
#include "saves.h"
#include "ODE.h"

using std::vector;

extern const int res 	= 1E4;
extern const double dt 	= 1E3/res;
extern const double h	= sqrt(dt);

// input arguments are a vector of length 8 with the connectivities and an integer setting the resolution of the grid
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	// Initializing the seeder.
	srand(time(0));

	// inputs
	double* Connectivity 	= mxGetPr (prhs[0]);
	const int T				= (int)(mxGetScalar(prhs[1]));
	const int onset			= (int)(mxGetScalar(prhs[2]));
	double* var_stim	 	= mxGetPr (prhs[3]);

	const int Time 			= (T+onset)*res;

	// Initializing the populations;
	Thalamic_Column Col(Connectivity);

	// setting up the data containers
	mxArray* Vt		= SetMexArray(1, T*red);

	int count = 0;
	for (int t=0; t<Time; ++t) {
		ODE (Col);
		if(t>=onset*res){
			get_data(count, Col, Vt);
			++count;
		}
	}

	// output of the simulation
	plhs[0] = getMexArray(Vt);
return;
}
