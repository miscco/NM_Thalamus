/*
*	Copyright (c) 2014 Michael Schellenberger Costa
*
*	Permission is hereby granted, free of charge, to any person obtaining a copy
*	of this software and associated documentation files (the "Software"), to deal
*	in the Software without restriction, including without limitation the rights
*	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*	copies of the Software, and to permit persons to whom the Software is
*	furnished to do so, subject to the following conditions:
*
*	The above copyright notice and this permission notice shall be included in
*	all copies or substantial portions of the Software.
*
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*	THE SOFTWARE.
*/

/****************************************************************************************************/
/*		Main file for compilation tests																*/
/*		The Simulation requires the following boost libraries:	Preprocessor						*/
/*																Random								*/
/****************************************************************************************************/
#include <iostream>
#include <ctime>
#include "Thalamic_Column.h"

/****************************************************************************************************/
/*										Fixed simulation settings									*/
/****************************************************************************************************/
extern const int T		= 30;								/* Simulation length s					*/
extern const int res 	= 1E4;								/* number of iteration steps per s		*/
extern const int red 	= res/100;							/* number of iterations that is saved	*/
extern const double dt 	= 1E3/res;							/* duration of a timestep in ms			*/
extern const double h	= sqrt(dt);							/* squareroot of dt for SRK iteration	*/
/****************************************************************************************************/
/*										 		end			 										*/
/****************************************************************************************************/


/****************************************************************************************************/
/*									Constants for SRK4 iteration									*/
/****************************************************************************************************/
extern const vector<double> B1 = {0,
								  0.626708569400000081728308032325,
								  1.7296310295000001389098542858846,
		 	 	 	 	 	 	  1.2703689705000000831347506391467};
extern const vector<double> B2 = {0,
								  0.78000033203198970710445792065002,
								  1.28727807507536762265942797967,
								  0.44477273249350995909523476257164};
/****************************************************************************************************/
/*										 		end													*/
/****************************************************************************************************/


/****************************************************************************************************/
/*										Main simulation routine										*/
/****************************************************************************************************/
int main(void) {
	/* Initialize the populations */
	Thalamic_Column Thalamus;

	/* Takes the time of the simulation */
	time_t start,end;
	time (&start);

	/* Simulation */
	for (int t=0; t< T*res; ++t) {
		Thalamus.iterate_ODE();
	}
	time (&end);

	/* Time consumed by the simulation */
	double dif = difftime(end,start);
	std::cout << "simulation done!\n";
	std::cout << "took " << dif 	<< " seconds" << "\n";
	std::cout << "end\n";
}
/****************************************************************************************************/
/*										 		end			 										*/
/****************************************************************************************************/
