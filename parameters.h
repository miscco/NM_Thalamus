/*****************************************************************************************************/
/******************	parameter file containing al fixed values of the simulation	**********************/
/*****************************************************************************************************/
#pragma once
/*****************************************************************************************************/
/**********************************		 physical properties 		**********************************/
/*****************************************************************************************************/
// Time constants for exhibitory and inhibitory neurons in ms
#define tau_t 		1
#define tau_r 		1

// current scaling in cm^2
#define c			1.

// Calcium concentration
#define alpha_Cat	-52E-6			// influx per spike in nmol
#define alpha_Car	-50E-6			// influx per spike in nmol
#define tau_Cat		5				// calcium time contant in ms
#define Ca_0		2E-4

// Maximum firing rate in ms^-1
#define Qt_max		400E-3
#define Qr_max		400E-3

// Sigmoid threshold values in mV
#define theta_t		-45
#define theta_r		-45

// Standard deviation for threshold in mV
#define sigma_t		9
#define sigma_r		9

// Parameter for sigmoidal mapping (dimensionless)
#define C           (3.14159265/sqrt(3))

// PSP rise time in ms^-1
#define gamma_t		20E-3
#define gamma_r		100E-3
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/**********************************		 	conductivities 			**********************************/
/*****************************************************************************************************/
// Leak current
#define gL_t		0.01
#define gL_r		0.05
#define gLK_t		0.05
#define gLK_r		0.03

// synaptic current
#define g_AMPA		0.1
#define g_GABA		0.15

// I_T current
#define gTt			2.2
#define gTr			2

// I_h current
#define gh			0.1

// KCa current
#define gKCa		10.05

// CAN current
#define gCAN		1
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/**********************************		 reversal potentials 		**********************************/
/*****************************************************************************************************/
// synaptic inputs in mV
#define V_rev_e  	0
#define V_rev_i  	-70

// Leak current
#define E_L_t		-70
#define E_L_r		-55
#define E_LK_t		-95
#define E_LK_r		-95

// I_T current
#define E_T			120

// I_h current
#define E_h			-40

// KCa current
#define E_KCa		-90

// CAN current
#define E_CAN		-20
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/**********************************		I_h activation parameters	**********************************/
/*****************************************************************************************************/
#define k1			2.5E7
#define k2			8E-4
#define k3			1E-1
#define k4			1E-3
#define n_P			4
#define g_inc		2
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/**********************************			noise parameters		**********************************/
/*****************************************************************************************************/
#define s			0.1
#define phi_st		5E-3
#define phi_inp		0.0
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/
