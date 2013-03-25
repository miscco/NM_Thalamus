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
	: Vt 	 (_INIT(-80)), 	Vr 	  	(_INIT(-80)), 	Cat	  	(_INIT(Ca_0)), 	Car	  	(_INIT(Ca_0)),
	  Phi_tt (_INIT(0.0)), 	Phi_tr 	(_INIT(0.0)), 	Phi_rt 	(_INIT(0.0)), 	Phi_rr 	(_INIT(0.0)),
	  x_tt 	 (_INIT(0.0)), 	x_tr   	(_INIT(0.0)), 	x_rt   	(_INIT(0.0)), 	x_rr	(_INIT(0.0)),
	  h_T_t	 (_INIT(0.0)),	h_T_r  	(_INIT(0.0)),   m_CANt	(_INIT(0.0)), 	m_CANr	(_INIT(0.0)),
	  m_KCat (_INIT(0.0)), 	m_KCar	(_INIT(0.0)), 	m_h		(_INIT(0.0)), 	m_h2	(_INIT(0.0)),
	  P_h	 (_INIT(0.0)),
	  N_tr 	 (210), 	   	N_rt   	(410), 			N_rr 	(800)
	{}

	// Constructors
	Thalamic_Colum(double* Con)
	: Vt 	 (_INIT(-80)), 	Vr 	  	(_INIT(-80)), 	Cat		(_INIT(Ca_0)), 	Car	  	(_INIT(Ca_0)),
	  Phi_tt (_INIT(0.0)), 	Phi_tr 	(_INIT(0.0)), 	Phi_rt	(_INIT(0.0)), 	Phi_rr 	(_INIT(0.0)),
	  x_tt 	 (_INIT(0.0)), 	x_tr   	(_INIT(0.0)), 	x_rt	(_INIT(0.0)), 	x_rr 	(_INIT(0.0)),
	  h_T_t	 (_INIT(0.0)),	h_T_r  	(_INIT(0.0)),   m_CANt	(_INIT(0.0)), 	m_CANr	(_INIT(0.0)),
	  m_KCat (_INIT(0.0)), 	m_KCar	(_INIT(0.0)), 	m_h		(_INIT(0.0)), 	m_h2	(_INIT(0.0)),
	  P_h	 (_INIT(0.0)),
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
	double 	I_T_t		(int) const;
	double 	I_T_r		(int) const;

	// h-type current
	double 	I_h			(int) const;
	double  m_inf_h		(int) const;
	double  tau_m_h		(int) const;

	// CAN current
	double I_CAN_t		(int) const;
	double I_CAN_r		(int) const;

	// KCa current
	double I_KCa_t		(int) const;
	double I_KCa_r		(int) const;

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
					Cat,		// Calcium concentration 	 of TC population
					Car,		// Calcium concentration 	 of RE population
					Phi_tt,		// PostSP from TC population to TC population
					Phi_tr,		// PostSP from TC population to RE population
					Phi_rt,		// PostSP from RE population to TC population
					Phi_rr,		// PostSP from RE population to RE population
					x_tt,		// derivative of Phi_ee
					x_tr,		// derivative of Phi_ei
					x_rt,		// derivative of Phi_ie
					x_rr,		// derivative of Phi_ii
					h_T_t,		// inactivation of T channel
					h_T_r,		// inactivation of T channel
					m_CANt,		// activation of CAN channel
					m_CANr,		// activation of CAN channel
					m_KCat,		// activation of KCa channel
					m_KCar,		// activation of KCa channel
					m_h,		// activation of h   channel
					m_h2,		// activation of h   channel bound
					P_h;		// fraction of bound calcium

	// connectivities
	double			N_tr,		// TC to RE loop
					N_rt,		// RE to TC loop
					N_rr;		// RE self  loop
};

