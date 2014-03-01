/*****************************************************************************************************/
/***********************	header file of a complete thalamic nuclei	******************************/
/*****************************************************************************************************/
#pragma once
#include <vector>
#include "macros.h"
#include "parameters.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>
using std::vector;

// typedefs for the RNG
typedef boost::mt11213b                    	ENG;    // Mersenne Twister
typedef boost::normal_distribution<double>	DIST;   // Normal Distribution
typedef boost::variate_generator<ENG,DIST> 	GEN;    // Variate generator

// implementation of the thalamic module
class Thalamic_Column {
public:
	// Constructors
	Thalamic_Column(void)
	: Vt 	(_INIT(E_L_t)), Vr 	  	(_INIT(E_L_r)),	Cat	  	(_INIT(Ca_0)), 	Car	  	(_INIT(Ca_0)),
	  Phi_tt(_INIT(0.0)), 	Phi_tr 	(_INIT(0.0)), 	Phi_rt 	(_INIT(0.0)), 	Phi_rr 	(_INIT(0.0)),
	  x_tt 	(_INIT(0.0)), 	x_tr   	(_INIT(0.0)), 	x_rt   	(_INIT(0.0)),  	x_rr	(_INIT(0.0)),
	  h_T_t	(_INIT(0.0)),	h_T_r  	(_INIT(0.0)),	m_T_t  	(_INIT(0.0)),	m_T_r	(_INIT(0.0)),
	  m_KCa	(_INIT(0.0)),	m_CAN  	(_INIT(0.0)),	m_h		(_INIT(0.0)),	m_h2	(_INIT(0.0)),
	  P_h	(_INIT(0.0)),
	  N_tr 	(210), 		   	N_rt   	(410), 			N_rr 	(800)
	{MTRands   = {{ENG(rand()), DIST (mphi_t, dphi_t)}, {ENG(rand()), DIST (mphi_t, dphi_t)}};
	 Rand_vars = {MTRands[0](), MTRands[1]()};}

	// Constructors
	Thalamic_Column(double* Con)
	: Vt 	(_INIT(0)), 	Vr 	  	(_INIT(0)), 	Cat	  	(_INIT(Ca_0)), 	Car	  	(_INIT(Ca_0)),
	  Phi_tt(_INIT(0.0)), 	Phi_tr 	(_INIT(0.0)), 	Phi_rt 	(_INIT(0.0)), 	Phi_rr 	(_INIT(0.0)),
	  x_tt 	(_INIT(0.0)), 	x_tr   	(_INIT(0.0)), 	x_rt   	(_INIT(0.0)),  	x_rr	(_INIT(0.0)),
	  h_T_t	(_INIT(0.0)),	h_T_r  	(_INIT(0.0)),	m_T_t  	(_INIT(0.0)),	m_T_r	(_INIT(0.0)),
	  m_KCa	(_INIT(0.0)),	m_CAN  	(_INIT(0.0)),	m_h		(_INIT(0.0)),	m_h2	(_INIT(0.0)),
	  P_h	(_INIT(0.0)),
	  N_tr 	 (Con[0]), 	   	N_rt	(Con[1]), 		N_rr	(Con[2])
	{MTRands   = {{ENG(rand()), DIST (mphi_t, dphi_t)}, {ENG(rand()), DIST (mphi_t, dphi_t)}};
	 Rand_vars = {MTRands[0](), MTRands[1]()};}

	// firing rate functions
	double 	get_Qt		(int) const;
	double 	get_Qr		(int) const;

	// synaptic current functions
	double 	I_et		(int) const;
	double 	I_it		(int) const;
	double 	I_er		(int) const;
	double 	I_ir		(int) const;

	// activation functions
	double  m_inf_T_t	(int) const;
	double  m_inf_T_r	(int) const;
	double  tau_m_T_t	(int) const;
	double  tau_m_T_r	(int) const;
	double  m_inf_h		(int) const;
	double  tau_m_h		(int) const;

	// deactivation functions
	double  h_inf_T_t	(int) const;
	double  h_inf_T_r	(int) const;
	double  tau_h_T_t	(int) const;
	double  tau_h_T_r	(int) const;

	// current functions
	double 	I_L_t		(int) const;
	double 	I_L_r		(int) const;
	double 	I_LK_t		(int) const;
	double 	I_LK_r		(int) const;
	double 	I_T_t		(int) const;
	double 	I_T_r		(int) const;
	double 	I_h			(int) const;
	double 	I_KCa		(int) const;
	double 	I_CAN		(int) const;

	// noise functions
	double 	noise_xRK 	(int) const;

	// ODE functions
	void 	set_RK		(int);
	void 	add_RK	 	(void);

	// function to extract the data
	friend void get_data (int, Thalamic_Column&, _REPEAT(double*, 1));

private:
	// population variables
	vector<double> 	Vt,			// TC membrane voltage
					Vr,			// RE membrane voltage
					Cat,		// Calcium concentration 	 of TC population
					Car,		// Calcium concentration 	 of RE population
					Phi_tt,		// PostSP from TC population to TC population
					Phi_tr,		// PostSP from TC population to RE population
					Phi_rt,		// PostSP from RE population to TC population
					Phi_rr,		// PostSP from RE population to RE population
					x_tt,		// derivative of Phi_tt
					x_tr,		// derivative of Phi_tr
					x_rt,		// derivative of Phi_rt
					x_rr,		// derivative of Phi_rr
					h_T_t,		// inactivation of T channel
					h_T_r,		// inactivation of T channel
					m_T_t,		// activation 	of T channel
					m_T_r,		// activation 	of T channel
					m_KCa,		// activation   of KCa channel
					m_CAN,		// activation   of CAN channel
					m_h,		// activation 	of h   channel
					m_h2,		// activation 	of h   channel bound with protein
					P_h;		// fraction of protein bound with calcium

	// connectivities
	double			N_tr,		// TC to RE loop
					N_rt,		// RE to TC loop
					N_rr;		// RE self  loop

	// random number generators
	vector<GEN>		MTRands;

	// container for random numbers
	vector<double>	Rand_vars;
};

