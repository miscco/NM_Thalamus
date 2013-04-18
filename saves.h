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
inline void get_data(int counter, Thalamic_Column& Col,  	vector<double>& Vt, 	vector<double>& Vr,
		vector<double>& Cat,		vector<double>& Car,	vector<double>& I_T_t,	vector<double>& I_T_r,
		vector<double>& I_h) {
	Vt 		[counter] = Col.Vt 		[0];
	Vr 		[counter] = Col.Vr 		[0];
	Cat		[counter] = Col.Cat		[0];
	Car		[counter] = Col.Phi_tt	[0];
	I_T_t	[counter] = Col.I_T_t	(0);
	I_T_r	[counter] = Col.I_T_r	(0);
	I_h		[counter] = Col.I_h		(0);
}
