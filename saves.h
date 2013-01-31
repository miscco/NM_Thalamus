#include <iostream>
#include <vector>
#include "Thalamic_Colum.h"
using std::vector;

// saving file for the mex compilation

// function to copy a std::vector into a matlab matrix
mxArray * getMexArray(const std::vector<double>& v){
    mxArray * mx = mxCreateDoubleMatrix(1,v.size(), mxREAL);
    std::copy(v.begin(), v.end(), mxGetPr(mx));
    return mx;
}


// saving the fluctuations of the populations
inline void get_data(int counter, Thalamic_Colum& Col, vector<double>& Ve, vector<double>& Vi, vector<double>& Phi_ee,
		vector<double>& Phi_ei, vector<double>& Phi_ie, vector<double>& Phi_ii,	vector<double>& I_T) {
	Ve 		[counter] = Col.Ve 		[0];
	Vi 		[counter] = Col.Vi 		[0];
	Phi_ee 	[counter] = Col.Phi_ee 	[0];
	Phi_ei 	[counter] = Col.Phi_ei 	[0];
	Phi_ie 	[counter] = Col.Phi_ie 	[0];
	Phi_ii 	[counter] = Col.Phi_ii 	[0];
	I_T		[counter] = Col.I_T		(0);
}
