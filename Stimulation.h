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
	/* empty constructor for compiling */
	Stim(void);

	Stim(Thalamic_Column& T, double* var)
	{ Thalamus = &T;
	  setup(var);}

	/* setup with respect to stimulation mode */
	void setup		(double* var_stim) {
		extern const int onset;
		extern const int res;
		extern const int dt;

		/* mode of stimulation */
		mode		= (int) var_stim[0];

		/* scale the stimulation strength from s^-1 to ms^-1 */
		strength 	= 		var_stim[1] / 1000;

		/* scale duration from ms to dt */
		duration 	= (int) var_stim[2] * res / 1000;

		/* scale the ISI from s to ms^-1 */
		ISI 		= (int) var_stim[3] * res;

		/* scale time to stimulus from ms to dt */
		time_to_stim= (int) var_stim[4] * res / 1000;

		if(mode==1) {
			time_to_stim = (onset+1) * res;
		}

		correction = onset * res;

	}

	void check_stim	(int time) {

		/* check if stimulation should start */
		switch (mode) {

		/* no stimulation */
		default:
			break;

		/* periodic stimulation */
		case 1:
			/* check if time is reached */
			if(time == time_to_stim) {
				/* switch stimulation on */
				stimulation_started 	= true;
				Thalamus->set_input(strength);

				/* update the timer */
				time_to_stim += ISI;
			}
			break;

		}

		/* wait to switch the stimulation off */
		if(stimulation_started) {
			count_duration++;

			/* switch stimulation off */
			if(count_duration==duration) {
				stimulation_started 	= false;
				count_duration			= 0;
				Thalamus->set_input(0.0);
			}
		}
	}

private:

	/* Stimulation parameters */
	/* stimulation strength */
	double strength 	= 0.0;

	/* duration of the stimulation */
	int duration 		= 500;

	/* inter stimulus intervall in case of periodic stimulation */
	int ISI				= 5E4;

	/* time until stimulus after minimum was found */
	int	time_to_stim	= 5500;

	/* mode of stimulation 				*/
	/* 0 == none 						*/
	/* 1 == periodic 					*/
	int mode			= 0;

	/* Internal variables */
	/* Simulation on for TRUE and off for FALSE */
	bool stimulation_started= false;

	/* onset in timesteps to correct the given time of the markers */
	int correction			= 10000;

	/* counter for stimulation duration */
	int count_duration		= 0;

	/* counter after minimum */
	int count_to_start 		= 0;

	/* pointer to thalamic column */
	Thalamic_Column* Thalamus;

};
/****************************************************************************************************/
/*										 		end													*/
/****************************************************************************************************/
