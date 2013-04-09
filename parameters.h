#pragma once
// Time constants for exhibitory and inhibitory neurons in ms
#define tau_t 		30
#define tau_r 		30

// Resting potential for exhibitory and inhibitory neurons in mV
#define V_t0 	 	-68
#define V_r0 	 	-72

// Reversal potential of exhibitory and inhibitory neurons in mV
#define Vt_rev_e  	0
#define Vt_rev_i  	-80
#define Vr_rev_e  	0
#define Vr_rev_i  	-70

// Maximum firing rate in ms^-1
#define Qt_max		30E-3
#define Qr_max		60E-3

#define Qt_burst	150E-3
#define Qr_burst	300E-3

// Sigmoid threshold values in mV
#define theta_t		-58.5
#define theta_r		-58.5

// Standard deviation for threshold in mV
#define sigma_t		6
#define sigma_r		4

// Parameter for sigmoidal mapping (dimensionless)
#define C           (3.14159265/sqrt(3))

// PSP rise time in ms^-1
#define gamma_t		70E-3
#define gamma_r		80E-3

// T-type current parameters
#define VT			120
#define gTt			2.2
#define gTr			3.0

// h-type current parameters
#define k1			2.5
#define k2			4E-4
#define k3			1E-1
#define k4			1E-3
#define n_P			2

#define E_h			-40
#define gh			0.02
#define g_inc		2

// current scaling
#define c			25.

// Calcium parameter
#define alpha_Ca	-0.002
#define tau_Ca		40
#define Ca_0		2E-4

// scaling of extrinsic input
#define s			0.1
#define phi_st		0.0
#define phi_inp		0.0
