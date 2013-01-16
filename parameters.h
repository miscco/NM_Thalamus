#pragma once

// Time constants for exhibitory and inhibitory neurons in ms
#define tau_e 		50
#define tau_i 		50

// Resting potential for exhibitory and inhibitory neurons in mV
#define V_e0 	 	-60
#define V_i0 	 	-60

// Reversal potential of exhibitory and inhibitory neurons in mV
#define V_rev_e  	0
#define V_rev_i  	-70

// Synaptic gain at resting voltage in mV * ms
#define rho_e 		2.4
#define rho_i 		-5.9

// Local axonal connectivity (dimensionless)

#define Ne	 		410
#define Ni	 		800

// Maximum firing rate in ms^-1
#define Qe_max		30E-3
#define Qi_max		60E-3

// Sigmoid threshold values in mV
#define theta_e		-58.5
#define theta_i		-58.5

// Standard deviation for threshold in mV
#define sigma_e		4
#define sigma_i		6

// Parameter for sigmoidal mapping (dimensionless)
#define C           (3.14159265/sqrt(3))

// PSP decay rates in ms^-1
#define alpha_ee	68E-3
#define alpha_ei	176E-3
#define alpha_ie	47E-3
#define alpha_ii	82E-3

// PSP rise rates in ms^-1
#define beta_ee	500E-3
#define beta_ei	500E-3
#define beta_ie	500E-3
#define beta_ii	500E-3

// scaling of extrinsiic input
#define s			0.1
