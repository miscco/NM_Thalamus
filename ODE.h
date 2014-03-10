/****************************************************************************************************/
/*									Implementation of the ODE solver								*/
/****************************************************************************************************/
#pragma once
#include "Thalamic_Column.h"

/****************************************************************************************************/
/*										Evaluation of SRK4											*/
/****************************************************************************************************/
inline void ODE(Thalamic_Column& Thalamus) {
	// first calculating every ith RK moment
	// has to be in order, 1th moment first
	for (int i=1; i<=4; ++i) {
		Thalamus.set_RK(i);
	}
	Thalamus.add_RK();
}
/****************************************************************************************************/
/*										 		end													*/
/****************************************************************************************************/


/****************************************************************************************************/
/*									Parameters for SRK4	integration									*/
/****************************************************************************************************/
extern const vector<double> B1 = {0,
								  0.626708569400000081728308032325,
								  1.7296310295000001389098542858846,
		 	 	 	 	 	 	  1.2703689705000000831347506391467};
extern const vector<double> B2 = {0,
								  0.78000033203198970710445792065002,
								  1.28727807507536762265942797967,
								  0.44477273249350995909523476257164};
/****************************************************************************************************/
/*										 		end													*/
/****************************************************************************************************/
