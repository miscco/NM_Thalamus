#include <vector>
#include "Thalamic_Colum.h"

// function that evaluates ODE using stochastic Runge Kutta
inline void ODE(Thalamic_Colum& Col, double ut1, double ut2) {
	for (auto i=1; i<=4; ++i) {
		Col.set_RK(i, ut1, ut2);
	}
	Col.add_RK(ut1);
}

// function that evaluates ODE using Euler-Maruyama
inline void ODE2(Thalamic_Colum& Col, double ut) {
	Col.set_Euler(ut);
}
