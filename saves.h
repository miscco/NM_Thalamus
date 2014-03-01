/*****************************************************************************************************/
/***********************			functions for data storage			******************************/
/*****************************************************************************************************/
#include <iostream>
#include <vector>
#include "Thalamic_Column.h"
using std::vector;

// saving file for the mex compilation
// saving the fluctuations of the populations
inline void get_data(int counter, Thalamic_Column& Col,	double* Vt) {

	Vt 		[counter] = Col.Vt 		[0];
}

// function to create a MATLAB data container
mxArray* SetMexArray(int N, int M) {
	mxArray* Array	= mxCreateDoubleMatrix(0, 0, mxREAL);
    mxSetM(Array, N);
    mxSetN(Array, M);
    mxSetData(Array, mxMalloc(sizeof(double)*M*N));
    return Array;
}
