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
inline void get_data(int counter, Thalamic_Colum& Col,  vector<double>& Vt, 	vector<double>& Vr, 	vector<double>& Ca,
		vector<double>& Phi_tt,	vector<double>& Phi_tr, vector<double>& Phi_rt, vector<double>& Phi_rr,	vector<double>& h_T_t,
		vector<double>& h_T_r,	vector<double>& I_T_t,  vector<double>& I_T_r) {
	Vt 		[counter] = Col.Vt 		[0];
	Vr 		[counter] = Col.Vr 		[0];
	Ca 		[counter] = Col.Ca 		[0];
	Phi_tt 	[counter] = Col.Phi_tt 	[0];
	Phi_tr 	[counter] = Col.Phi_tr 	[0];
	Phi_rt 	[counter] = Col.Phi_rt 	[0];
	Phi_rr 	[counter] = Col.Phi_rr 	[0];
	h_T_t	[counter] = Col.h_T_t	[0];
	h_T_r	[counter] = Col.theta_h	[0];
	I_T_t	[counter] = Col.I_T_t	(0);
	I_T_r	[counter] = Col.I_h		(0);
}
