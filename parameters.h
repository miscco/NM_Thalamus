#pragma once
// Time constants for exhibitory and inhibitory neurons in ms
#define tau_t 		50
#define tau_r 		50

// Leak current parameters
#define gL_t		0.01
#define gL_r		0.025
#define gLK_t		0.04
#define gLK_r		0.025

#define E_L_t		-55
#define E_L_r		-60
#define E_LK_t		-100
#define E_LK_r		-95

// Reversal potential of exhibitory and inhibitory neurons in mV
#define Vt_rev_e  	0
#define Vt_rev_i  	-80
#define Vr_rev_e  	0
#define Vr_rev_i  	-70

// Maximum firing rate in ms^-1
#define Qt_max		0E-3
#define Qr_max		0E-3

#define Qt_burst	400E-3
#define Qr_burst	400E-3

// Sigmoid threshold values in mV
#define theta_t		-45
#define theta_r		-45

// Standard deviation for threshold in mV
#define sigma_t		4
#define sigma_r		4

// Parameter for sigmoidal mapping (dimensionless)
#define C           (3.14159265/sqrt(3))

// PSP rise time in ms^-1
#define gamma_t		70E-3
#define gamma_r		80E-3

// T-type current parameters
#define E_T			120
#define gTt			2.0
#define gTr			1.75

// h-type current parameters
#define k1			2.5E7
#define k2			4E-4
#define k3			1E-1
#define k4			1E-3
#define n_P			4

#define E_h			-40
#define gh			0.04
#define g_inc		2

// current scaling
#define c			50.

// Calcium parameter
#define alpha_Cat	-0.0001
#define alpha_Car	-0.00052
#define Ca_0		2E-4

// KCa current parameters
#define gKCa		10.05
#define E_KCa		-90

// CAN current parameters
#define gCAN		1
#define E_CAN		-20

// scaling of extrinsic input
#define s			0.1
#define phi_st		0.000
#define phi_inp		0.0
