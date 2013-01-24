#pragma once

// Time constants for exhibitory and inhibitory neurons in ms
#define tau_e 		50
#define tau_i 		50

// Resting potential for exhibitory and inhibitory neurons in mV
#define V_e0 	 	-64
#define V_i0 	 	-64

// Reversal potential of exhibitory and inhibitory neurons in mV
#define V_rev_e  	0
#define V_rev_i  	-70

// Synaptic gain at resting voltage in mV * ms
#define rho_e 		1
#define rho_i 		-1.05

// Local axonal connectivity (dimensionless)
#define Ne	 		410
#define Ni	 		800

// Maximum firing rate in ms^-1
#define Qe_max		30.E-3
#define Qi_max		60.E-3

// Sigmoid threshold values in mV
#define theta_e		-58.5
#define theta_i		-58.5

// Standard deviation for threshold in mV
#define sigma_e		4
#define sigma_i		6

// Parameter for sigmoidal mapping (dimensionless)
#define C           (3.14159265/sqrt(3))

// PSP rise time in ms^-1
#define gamma_ee	70E-3
#define gamma_ei	70E-3
#define gamma_ie	58.6E-3
#define gamma_ii	58.6E-3

// scaling of extrinsic input
#define s			0.1
#define phi_sc		1.5
