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
/*								Implementation of the stimulation protocol							*/
/****************************************************************************************************/
#pragma once
#include "Thalamic_Column.h"

/****************************************************************************************************/
/*											Stimulation object										*/
/****************************************************************************************************/
class Stim {
public:
	/* Empty constructor for compiling */
	Stim(void);

	Stim(Thalamic_Column& T, double* var)
	{ Thalamus = &T;
	  setup(var);}

	/* Setup with respect to stimulation mode */
	void setup		(double* var_stim) {
		extern const int onset;
		extern const int res;
		extern const int dt;

		/* Mode of stimulation */
		mode		= (int) var_stim[0];

		/* Scale the stimulation strength from s^-1 to ms^-1 */
		strength 	= 		var_stim[1] / 1000;

		/* Scale duration from ms to dt */
		duration 	= (int) var_stim[2] * res / 1000;

		/* Scale the ISI from s to ms^-1 */
		ISI 		= (int) var_stim[3] * res;

		/* Scale time to stimulus from ms to dt */
		time_to_stim= (int) var_stim[4] * res / 1000;

		if(mode==1) {
			time_to_stim = (onset+1) * res;
		}

		correction = onset * res;

	}

	void check_stim	(int time) {

		/* Check if stimulation should start */
		switch (mode) {

		/* No stimulation */
		default:
			break;

		/* Periodic stimulation */
		case 1:
			/* Check if time is reached */
			if(time == time_to_stim) {
				/* Switch stimulation on */
				stimulation_started 	= true;
				Thalamus->set_input(strength);

				/* Update the timer */
				time_to_stim += ISI;

				/* Update the marker */
				marker_stimulation.push_back(time - correction);
			}
			break;
		}

		/* Wait to switch the stimulation off */
		if(stimulation_started) {
			count_duration++;

			/* Switch stimulation off */
			if(count_duration==duration) {
				stimulation_started 	= false;
				count_duration			= 0;
				Thalamus->set_input(0.0);
			}
		}
	}

	/* Create MATLAB container for marker storage */
	mxArray* get_marker(void) {
		mxArray* Marker	= mxCreateDoubleMatrix(0, 0, mxREAL);
	    mxSetM(Marker, 1);
	    mxSetN(Marker, marker_stimulation.size());
	    mxSetData(Marker, mxMalloc(sizeof(double)*marker_stimulation.size()));
		double* Pr_Marker	= mxGetPr(Marker);
		for(unsigned i=0; i<marker_stimulation.size(); ++i) {
			Pr_Marker[i] = marker_stimulation[i];
		}
		return Marker;
	}

private:

	/* Stimulation parameters */
	/* Stimulation strength */
	double strength 	= 0.0;

	/* Duration of the stimulation */
	int duration 		= 500;

	/* Inter stimulus intervall in case of periodic stimulation */
	int ISI				= 5E4;

	/* Threshold for phase dependent stimulation */
	double threshold	= -80;

	/* Time until stimulus after minimum was found */
	int	time_to_stim	= 5500;

	/* Mode of stimulation 				*/
	/* 0 == none 						*/
	/* 1 == periodic 					*/
	int mode			= 0;

	/* Internal variables */
	/* Simulation on for TRUE and off for FALSE */
	bool stimulation_started= false;

	/* Threshold has been reached */
	bool threshold_crossed	= false;

	/* Minimum found */
	bool minimum_found		= false;

	/* Onset in timesteps to correct the given time of the markers */
	int correction			= 10000;

	/* Counter for stimulation duration */
	int count_duration		= 0;

	/* Pointer to thalamic column */
	Thalamic_Column* Thalamus;

	/* Data containers */
	std::vector<int>	marker_stimulation;
};
/****************************************************************************************************/
/*										 		end													*/
/****************************************************************************************************/
