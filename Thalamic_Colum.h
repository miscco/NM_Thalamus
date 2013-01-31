#pragma once
#include <cmath>
#include <vector>
#include "macros.h"
#include "parameters.h"
using std::vector;

// implementation of the cortical module after Zavaglia2006

class Thalamic_Colum {
public:
	// Constructors
	Thalamic_Colum(void)
	: Ve 	 (_INIT(-80)), Vi 	  (_INIT(-80)),
	  Phi_ee (_INIT(0.0)), Phi_ei (_INIT(0.0)), Phi_ie (_INIT(0.0)), Phi_ii (_INIT(0.0)),
	  x_ee 	 (_INIT(0.0)), x_ei   (_INIT(0.0)), x_ie   (_INIT(0.0)), x_ii 	(_INIT(0.0)),
	  h_T 	 (_INIT(0.0)),
	  N_ti 	 (210), 		N_it   (410), 		  N_ii 	 (800)
	{}

	// Constructors
	Thalamic_Colum(double* Con)
	: Ve 	 (_INIT(-80)), Vi 	  (_INIT(-80)),
	  Phi_ee (_INIT(0.0)), Phi_ei (_INIT(0.0)), Phi_ie (_INIT(0.0)), Phi_ii (_INIT(0.0)),
	  x_ee 	 (_INIT(0.0)), x_ei   (_INIT(0.0)), x_ie   (_INIT(0.0)), x_ii 	(_INIT(0.0)),
	  h_T 	 (_INIT(0.0)),
	  N_ti 	 (Con[0]), 		N_it   (Con[1]), 		  N_ii 	 (Con[2])
	{}

	// firing rate functions
	double 	get_Qe		(int) const;
	double 	get_Qi		(int) const;

	// membrane response functions
	double 	psi_ee		(int) const;
	double 	psi_ei		(int) const;
	double 	psi_ie		(int) const;
	double 	psi_ii		(int) const;

	// T-type current instant activation variable
	double  m_inf		(int) const;

	// T-type current
	double I_T			(int) const;

	// noise functions
	double 	noise_xRK 	(int, double, double) const;
	double 	noise_xE 	(double) 		  	  const;

	// ODE functions
	void 	set_RK		(int, double, double, double, double);
	void 	set_Euler	(double, double);
	void 	add_RK	 	(double, double);

	// function to extract the data
	friend void get_data (int, Thalamic_Colum&, _REPEAT(vector<double>&, 2));
	friend void get_data (int, Thalamic_Colum&, _REPEAT(vector<double>&, 7));

private:
	// population variables
	vector<double> 	Ve,			// exitatory membrane voltage
					Vi,			// exitatory membrane voltage
					Phi_ee,		// PostSP from TC population to TC population
					Phi_ei,		// PostSP from TC population to RE population
					Phi_ie,		// PostSP from RE population to TC population
					Phi_ii,		// PostSP from RE population to RE population
					x_ee,		// derivative of Phi_ee
					x_ei,		// derivative of Phi_ei
					x_ie,		// derivative of Phi_ie
					x_ii,		// derivative of Phi_ii
					h_T;		// inactivation of T current

	// connectivities
	double			N_ti,		// TC to RE loop
					N_it,		// RE to TC loop
					N_ii;		// RE self  loop
};

