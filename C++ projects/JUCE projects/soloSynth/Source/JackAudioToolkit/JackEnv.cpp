/*
  ==============================================================================

    Envelope.cpp
    Created: 14 Jul 2018 1:35:18pm
    Author:  J

  ==============================================================================
*/

#include "JackEnv.h"
#include <math.h>



void JackEnv::setSampleRate(double sampRate)
{
	sampleRate = sampRate;

}

void JackEnv::setAttack(double attackTimeMs)
{
	attack = 1 - pow(0.01, 1.0 / (attackTimeMs * sampleRate * 0.001));
}

void JackEnv::setDecay(double decayTimeMs)
{
	decay = pow(0.01, 1.0 / (decayTimeMs * sampleRate * 0.001));

}
void JackEnv::setSustain(double sustainLev)
{
	sustainLevel = sustainLev;

}
void JackEnv::setRelease(double releaseTimeMs)
{
	release = pow(0.01, 1.0 / (releaseTimeMs * sampleRate * 0.001));

}

double JackEnv::adsr(double input, int trigger)
{
	if (trigger == 1 && !attacking && !sustaining && !decaying) {
		sustainCount = 0;
		decaying = false;
		sustaining = false;
		releasing = false;
		attacking= true;
	}
	// ==== attack portion ===  
	if (attacking) {
		releasing = false;
		amplitude += (1 * attack);
		output = input*amplitude;

		if (amplitude >= 1) {
			amplitude = 1;
			attacking = false;
			decaying = true;
		}
	}

	// ==== Decay portion ===  

	if (decaying) {
		output = input*(amplitude *= decay);
		if (amplitude <= sustainLevel) {
			decaying = false;
			sustaining = true;
		}
	}
	// ==== Sustain portion ===  

	if (sustainCount<holdtime && sustaining) {
		output = input*amplitude;
		sustainCount++;
	}

	if (sustainCount >= holdtime && trigger == 1) {
		output = input*amplitude;
	}

	if (sustainCount >= holdtime && trigger != 1) {
		sustaining = false;
		releasing = true;
	}
	// ==== release portion ===  

	if (releasing && amplitude>0.) {
		output = input*(amplitude *= release);

	}

	return output;


}
