#pragma once
// Time constants for exhibitory and inhibitory neurons in ms
#define tau_t 		40
#define tau_r 		40

// Resting potential for exhibitory and inhibitory neurons in mV
#define V_t0 	 	-70
#define V_r0 	 	-77

// Reversal potential of exhibitory and inhibitory neurons in mV
#define Vt_rev_e  	0
#define Vt_rev_i  	-80
#define Vr_rev_e  	0
#define Vr_rev_i  	-70

// Synaptic gain at resting voltage in mV * ms
#define rho_e 		1
#define rho_i 		-1.05

// Maximum firing rate in ms^-1
#define Qt_max		30E-3
#define Qr_max		60E-3

#define Qt_burst	200E-3
#define Qr_burst	500E-3

// Sigmoid threshold values in mV
#define theta_t		-58.5
#define theta_r		-58.5

// Standard deviation for threshold in mV
#define sigma_t		4
#define sigma_r		6

// Parameter for sigmoidal mapping (dimensionless)
#define C           (3.14159265/sqrt(3))

// PSP rise time in ms^-1
#define gamma_t		70E-3
#define gamma_r		150E-3

// T-type current parameters
#define VT			120
#define gTt			2.2
#define gTr			3.0

// h-type current parameters
#define Vh			-43
#define gh			0.2

// parameters of the calcium adaption of h current
#define eta			1E-2
#define theta_0		-75
#define lambda		5

// current scaling
#define c			13.5

// Calcium parameter
#define alpha_Ca	-0.02
#define tau_Ca		5
#define Ca_0		0.1

// scaling of extrinsic input
#define s			0.1
#define phi_st		0.5
#define phi_inp		0.5
