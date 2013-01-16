#pragma once
#include <cmath>
#include <vector>
#include "macros.h"
#include "parameters.h"
using std::vector;

// implementation of the cortical module after Zavaglia2006

class Cortical_Colum {
public:
	// Constructors
	Cortical_Colum(void)
	: Ve 	 (_INIT(-68)), Vi 	  (_INIT(-68)),
	  Phi_ee (_INIT(0.0)), Phi_ei (_INIT(0.0)), Phi_ie (_INIT(0.0)), Phi_ii (_INIT(0.0)),
	  x_ee 	 (_INIT(0.0)), x_ei   (_INIT(0.0)), x_ie   (_INIT(0.0)), x_ii 	(_INIT(0.0))
	{}

	// firing rate functions
	double 	get_Qe		(int) const;
	double 	get_Qi		(int) const;

	// membrane respone functions
	double 	psi_ee		(int) const;
	double 	psi_ei		(int) const;
	double 	psi_ie		(int) const;
	double 	psi_ii		(int) const;

	// noise functions
	double 	noise_xRK 	(int, double, double) const;
	double 	noise_xE 	(double) 		  	  const;

	// ODE functions
	void 	set_RK		(int, double, double, double, double);
	void 	set_Euler	(double, double);
	void 	add_RK	 	(double, double);

	friend void get_data (int, Cortical_Colum&, vector<double>&, vector<double>&);

private:
	// population variables
	vector<double> 	Ve,			// exitatory membrane voltage
					Vi,			// exitatory membrane voltage
					Phi_ee,		// PostSP from exitatory  population to exitatory  population
					Phi_ei,		// PostSP from exitatory  population to inhibitory population
					Phi_ie,		// PostSP from inhibitory population to exitatory  population
					Phi_ii,		// PostSP from inhibitory population to inhibitory population
					x_ee,		// derivative of the Phi_ee
					x_ei,		// derivative of the Phi_ei
					x_ie,		// derivative of the Phi_ie
					x_ii;		// derivative of the Phi_ii
};

