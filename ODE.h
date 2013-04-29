/*****************************************************************************************************/
/***********************			ODE function of the system			******************************/
/*****************************************************************************************************/
#include <vector>
#include "Thalamic_Column.h"

// function that evaluates ODE using stochastic Runge Kutta
inline void ODE(Thalamic_Column& Col, double ut1, double ut2) {
	for (auto i=1; i<=4; ++i) {
		Col.set_RK(i, ut1, ut2);
	}
	Col.add_RK(ut1);
}
