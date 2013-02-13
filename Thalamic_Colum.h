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
	: Vt 	 (_INIT(-60)), 	Vr 	  	(_INIT(-60)), 	Ca 	  	(_INIT(0.1)),
	  Phi_tt (_INIT(0.0)), 	Phi_tr 	(_INIT(0.0)), 	Phi_rt 	(_INIT(0.0)), 	Phi_rr 	(_INIT(0.0)),
	  x_tt 	 (_INIT(0.0)), 	x_tr   	(_INIT(0.0)), 	x_rt   	(_INIT(0.0)), 	x_rr	(_INIT(0.0)),
	  h_T_t	 (_INIT(0.0)),	h_T_r  	(_INIT(0.0)), 	h_h_t	(_INIT(0.0)), 	theta_h	(_INIT(-75)),
	  N_tr 	 (210), 	   	N_rt   	(410), 			N_rr 	(800)
	{}

	// Constructors
	Thalamic_Colum(double* Con)
	: Vt 	 (_INIT(-80)), 	Vr 	  	(_INIT(-80)), 	Ca		(_INIT(0.1)),
	  Phi_tt (_INIT(0.0)), 	Phi_tr 	(_INIT(0.0)), 	Phi_rt	(_INIT(0.0)), 	Phi_rr 	(_INIT(0.0)),
	  x_tt 	 (_INIT(0.0)), 	x_tr   	(_INIT(0.0)), 	x_rt	(_INIT(0.0)), 	x_rr 	(_INIT(0.0)),
	  h_T_t	 (_INIT(0.0)), 	h_T_r  	(_INIT(0.0)),	h_h_t	(_INIT(0.0)), 	theta_h	(_INIT(-75)),
	  N_tr 	 (Con[0]), 	   	N_rt	(Con[1]), 		N_rr	(Con[2])
	{}

	// firing rate functions
	double 	get_Qt		(int) const;
	double 	get_Qr		(int) const;

	// membrane response functions
	double 	psi_et		(int) const;
	double 	psi_it		(int) const;
	double 	psi_er		(int) const;
	double 	psi_ir		(int) const;

	// T-type current activation
	double  m_inf_t		(int) const;
	double  m_inf_r		(int) const;

	// T-type current deactivation
	double  h_inf_t		(int) const;
	double  tau_h_t		(int) const;
	double  h_inf_r		(int) const;
	double  tau_h_r		(int) const;

	// T-type current
	double I_T_t		(int) const;
	double I_T_r		(int) const;

	// h-type current deactivation
	double  h_inf		(int) const;
	double  tau_h		(int) const;

	// h-type current
	double I_h		(int) const;

	// noise functions
	double 	noise_xRK 	(int, double, double) const;
	double 	noise_xE 	(double) 		  	  const;

	// ODE functions
	void 	set_RK		(int, double, double);
	void 	set_Euler	(double);
	void 	add_RK	 	(double);

	// function to extract the data
	friend void get_data (int, Thalamic_Colum&, _REPEAT(vector<double>&, 11));

private:
	// population variables
	vector<double> 	Vt,			// exitatory membrane voltage
					Vr,			// exitatory membrane voltage
					Ca,			// Calcium concentration 	 of TC population
					Phi_tt,		// PostSP from TC population to TC population
					Phi_tr,		// PostSP from TC population to RE population
					Phi_rt,		// PostSP from RE population to TC population
					Phi_rr,		// PostSP from RE population to RE population
					x_tt,		// derivative of Phi_ee
					x_tr,		// derivative of Phi_ei
					x_rt,		// derivative of Phi_ie
					x_rr,		// derivative of Phi_ii
					h_T_t,		// inactivation of T current
					h_T_r,		//   activation of T current
					h_h_t,		//   activation of h current
					theta_h;	// h current adaption

	// connectivities
	double			N_tr,		// TC to RE loop
					N_rt,		// RE to TC loop
					N_rr;		// RE self  loop
};

