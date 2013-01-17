#pragma once
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
vector<double> rand_var (int N, MTRand mtrand,double mean, double sd) {
	mtrand.seed();
	vector<double> dW(N);
	for (auto i=0; i<N; ++i){
		dW[i] = mtrand.randNorm(mean,sqrt(sd));
	}
	return dW;
}
