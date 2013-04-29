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
inline void get_data(int counter, Thalamic_Column& Col,	vector<double>& Vt, 	vector<double>& Vr,
		vector<double>& Cat,	vector<double>& Car,	vector<double>& Phi_tr,	vector<double>& Phi_rt,
		vector<double>& I_T_t,	vector<double>& I_T_r,	vector<double>& I_KCa,	vector<double>& I_CAN,
		vector<double>& I_h) {

	Vt 		[counter] = Col.Vt 		[0];
	Vr 		[counter] = Col.Vr 		[0];
	Cat		[counter] = Col.Cat		[0];
	Car		[counter] = Col.Car		[0];
	Phi_tr	[counter] = Col.Phi_tr	[0];
	Phi_rt	[counter] = Col.Phi_rt	[0];
	I_T_t	[counter] = Col.I_T_t	(0);
	I_T_r	[counter] = Col.I_T_r	(0);
	I_KCa	[counter] = Col.I_KCa	(0);
	I_CAN	[counter] = Col.I_CAN	(0);
	I_h		[counter] = Col.I_h		(0);
}
