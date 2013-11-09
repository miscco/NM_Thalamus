/*****************************************************************************************************/
/******************	functions for generation of noise and its evaluation in RK4	**********************/
/*****************************************************************************************************/
#pragma once
#include <cmath>
#include <vector>
#include "MersenneTwister.h"
using std::vector;

/*****************************************************************************************************/
/*****************************		parameters for integration of SRK4		**************************/
/*****************************************************************************************************/
// vectors needed for stochastic RK
extern const vector<double> B1 = {0,
								  0.626708569400000081728308032325,
								  1.7296310295000001389098542858846,
		 	 	 	 	 	 	  1.2703689705000000831347506391467};
extern const vector<double> B2 = {0,
								  0.78000033203198970710445792065002,
								  1.28727807507536762265942797967,
								  0.44477273249350995909523476257164};
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/**********************************		random input generation		**********************************/
/*****************************************************************************************************/
// function that creates a vector of random numbers with length N and SD sigma
vector<double> rand_var (MTRand mtrand, int length, double mean, double sd) {
	// length	length of the simulation
	// mean		mean noise without stimulation
	// sd 		its sd

	mtrand.seed();
	vector<double> dW(length);
	for (auto i=0; i<length; ++i){
		dW[i] = mtrand.randNorm(mean,sqrt(sd));
	}
	return dW;
}
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/


/*****************************************************************************************************/
/****************************		random input generation with stim		**************************/
/*****************************************************************************************************/
// function that creates a vector of random numbers with length N, given mean and standard deviation
// together with pulses of increased mean with frequency f and strength str
vector<double> rand_inp (MTRand mtrand, int length, double mean, double sd, int onset, double* var_stim) {
	// res			steps per secon
	// length		total length of the simulation
	// onset		time until data is saved
	// var_stim[0]	strength of stimulation
	// var_stim[0]	time between stimuli
	// var_stim[0]	length of stimuli
	// mean			mean noise without stimulation
	// sd 			its sd

	extern const double res;
	int mode 	= 0;
	int count 	= 0;

	double strength = mean + var_stim[0];

	// initializing the rando number generator
	mtrand.seed();
	// generating random noise for the whole time length
	vector<double> dW(length);
	for (auto i=0; i<length; ++i){
		if(i==(onset + 1 + count*var_stim[1])*res){
			mode = 1;
		}
		if(i==(onset + 1 + count*var_stim[1])*res+var_stim[2]){
			mode = 0;
			count++;
		}
		switch (mode) {
		case 0:
			dW[i] = mtrand.randNorm(mean,	 sqrt(sd));
			break;
		case 1:
			dW[i] = mtrand.randNorm(strength,sqrt(sd));
			break;
		}
	}
	return dW;
}
/*****************************************************************************************************/
/**********************************		 		end			 		**********************************/
/*****************************************************************************************************/
