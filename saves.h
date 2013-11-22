/*****************************************************************************************************/
/***********************			functions for data storage			******************************/
/*****************************************************************************************************/
#include <iostream>
#include <vector>
#include "Thalamic_Column.h"
using std::vector;

// saving file for the mex compilation

// function to copy a std::vector into a matlab matrix
mxArray * getMexArray(const std::vector<double>& v){
    mxArray * mx = mxCreateDoubleMatrix(1,v.size(), mxREAL);
    std::copy(v.begin(), v.end(), mxGetPr(mx));
    return mx;
}


// saving the fluctuations of the populations
inline void get_data(int counter, Thalamic_Column& Col,	vector<double>& Vt, 	vector<double>& Vr) {

	Vt 		[counter] = Col.Vt 		[0];
	Vr 		[counter] = Col.Vr 		[0];
}
