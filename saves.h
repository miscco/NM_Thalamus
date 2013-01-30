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
inline void get_data(int counter, Thalamic_Colum& Col, vector<double>& Ve, vector<double>& Vi) {
	Ve[counter] = Col.Ve[0];
	Vi[counter] = Col.Vi[0];
}
