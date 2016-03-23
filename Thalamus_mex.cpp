/*
 *	Copyright (c) 2015 University of Lübeck
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in
 *	all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *	THE SOFTWARE.
 *
 *	AUTHORS:	Michael Schellenberger Costa: mschellenbergercosta@gmail.com
 *
 *	Based on:	A thalamocortical neural mass model of the EEG during NREM sleep and its response
 *				to auditory stimulation.
 *				M Schellenberger Costa, A Weigenand, H-VV Ngo, L Marshall, J Born, T Martinetz,
 *				JC Claussen.
 *				PLoS Computational Biology (in review).
 */

/****************************************************************************************************/
/* 		Implementation of the simulation as MATLAB routine (mex compiler)							*/
/* 		mex command is given by:																	*/
/* 		mex CXXFLAGS="\$CXXFLAGS -std=c++11 -O3" Thalamus_mex.cpp Thalamic_Column.cpp				*/
/****************************************************************************************************/
#include "mex.h"
#include "matrix.h"
#include "Data_Storage.h"
mxArray* SetMexArray(int N, int M);

/****************************************************************************************************/
/*										Fixed simulation settings									*/
/****************************************************************************************************/
extern const int onset	= 15;								/* time until data is stored in  s		*/
extern const int res 	= 1E3;								/* number of iteration steps per s		*/
extern const int red 	= res/100;							/* number of iterations that is saved	*/
extern const double dt 	= 1E3/res;							/* duration of a timestep in ms			*/
extern const double h	= sqrt(dt);							/* squareroot of dt for SRK iteration	*/
/****************************************************************************************************/
/*										 		end			 										*/
/****************************************************************************************************/

/****************************************************************************************************/
/*										Simulation routine	 										*/
/*										lhs defines outputs											*/
/*										rhs defines inputs											*/
/****************************************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	/* Initialize the seeder */
	srand(time(NULL));

	/* Fetch inputs */
	const int T				= (int) (mxGetScalar(prhs[0]));	/* Duration of simulation in s			*/
	const int Time 			= (T+onset)*res;				/* Total number of iteration steps		*/
	double* Param_Thalamus	= mxGetPr (prhs[1]);			/* Parameters of cortical module		*/

	/* Initialize the populations */
	Thalamic_Column Thalamus(Param_Thalamus);

	/* Create data containers */
	mxArray* Vt		= SetMexArray(1, T*res/red);
	mxArray* Vr		= SetMexArray(1, T*res/red);
	mxArray* ah		= SetMexArray(1, T*res/red);

	/* Pointer to the actual data block */
	double* Pr_Vt	= mxGetPr(Vt);
	double* Pr_Vr	= mxGetPr(Vr);
	double* Pr_ah	= mxGetPr(ah);

	/* Simulation */
	int count = 0;
	for (int t=0; t<Time; ++t) {
		Thalamus.iterate_ODE();
		if(t>=onset*res && t%red==0){
			get_data(count, Thalamus, Pr_Vt, Pr_Vr, Pr_ah);
			++count;
		}
	}

	/* Output of the simulation */
	plhs[0] = Vt;
	plhs[1] = Vr;
	plhs[2] = ah;
return;
}
/****************************************************************************************************/
/*												end													*/
/****************************************************************************************************/


/****************************************************************************************************/
/*									Create MATLAB data container									*/
/****************************************************************************************************/
mxArray* SetMexArray(int N, int M) {
	mxArray* Array	= mxCreateDoubleMatrix(0, 0, mxREAL);
	mxSetM(Array, N);
	mxSetN(Array, M);
	mxSetData(Array, mxMalloc(sizeof(double)*M*N));
	return Array;
}
/****************************************************************************************************/
/*										 		end													*/
/****************************************************************************************************/
