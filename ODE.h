#include <vector>
#include "Thalamic_Colum.h"

// function that evaluates ODE using stochastic Runge Kutta
inline void ODE(Thalamic_Colum& Col, double uf1, double uf2, double up1, double up2) {
	for (auto i=1; i<=4; ++i) {
		Col.set_RK(i, uf1, uf2, up1, up2);
	}
	Col.add_RK(uf1, up1);
}

// function that evaluates ODE using Euler-Maruyama
inline void ODE2(Thalamic_Colum& Col, double uf1, double up1) {
	Col.set_Euler(uf1, up1);
}
