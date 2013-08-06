/*****************************************************************************************************/
/******************	functions for generation of noise and its evaluation in RK4	**********************/
/*****************************************************************************************************/
#pragma once
#include <cmath>
#include <vector>
#include "MersenneTwister.h"
using std::vector;

// vectors needed for stochastic RK
extern const vector<double> B1 = {0,
								  0.626708569400000081728308032325,
								  1.7296310295000001389098542858846,
		 	 	 	 	 	 	  1.2703689705000000831347506391467};
extern const vector<double> B2 = {0,
								  0.78000033203198970710445792065002,
								  1.28727807507536762265942797967,
								  0.44477273249350995909523476257164};

// function that creates a vector of random numbers with length N and SD sigma
vector<double> rand_var (MTRand mtrand, int length, double mean, double sd) {
	mtrand.seed();
	vector<double> dW(length);
	for (auto i=0; i<length; ++i){
		dW[i] = mtrand.randNorm(mean,sqrt(sd));
	}
	return dW;
}

// function that creates a vector of random numbers with length N and SD sigma
vector<double> rand_inp (MTRand mtrand, int res, int sec, int onset, int f, int len, double mean, double sd, double str) {
	// res		steps per secon
	// sec		length of the simulation
	// onset	time until stimulation starts
	// f		ISI
	// len		length of the stimulation in steps (of res)
	// mean		mean noise without stimulation
	// sd 		its sd
	// str 		stimulation strength

	int length 	= res*(sec+onset);
	int mode 	= 0;
	int count 	= 0;

	// initializing the rando number generator
	mtrand.seed();
	// generating random noise for the whole time length
	vector<double> dW(length);
	for (auto i=0; i<length; ++i){
		if(i==(onset+count*f)*res){
			mode = 1;
		}
		if(i==(onset+count*f)*res+len){
			mode = 0;
			count++;
		}
		switch (mode) {
		case 0:
			dW[i] = mtrand.randNorm(mean,sqrt(sd));
			break;
		case 1:
			dW[i] = mtrand.randNorm(mean + str,sqrt(sd));
			break;
		}
	}
	return dW;
}
