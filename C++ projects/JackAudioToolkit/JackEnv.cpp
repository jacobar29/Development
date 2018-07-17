/*
  ==============================================================================

    Envelope.cpp
    Created: 14 Jul 2018 1:35:18pm
    Author:  J

  ==============================================================================
*/

#include "JackEnv.h"
#include <math.h>

# define M_PI 3.14159265358979323846  // value of pi


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
JackFilter::JackFilter()
{
	sampleRate = 44100;
}

JackFilter::JackFilter(double sampleRateHz)
{
	sampleRate = sampleRateHz;}

void JackFilter::setSampleRate(double newSampleRate)
{
	sampleRate = newSampleRate;
}

double JackFilter::bandPass(double input, double cutoff1, double resonance)
{
	return 0.0;
}

// low pass filter algorithm inspired by the maximillian sound library (https://github.com/micknoise/Maximilian)
double JackFilter::lowPass(double input, double cutoffFreq, double resonance)
{
	cutoff = cutoffFreq;

	if (cutoff < 10)
		cutoff == 10;
	if (cutoff > sampleRate)
		cutoff = sampleRate;
	if (resonance < 1.) resonance = 1;
	

	// calculate number of poles
	z = cos((2 * M_PI)*cutoff / sampleRate);
	//calculate filter coefficient
	c = 2 - 2 * z;
	// resonance calculation
	double r = (sqrt(2.0)*sqrt(-pow((z - 1.0), 3.0)) + resonance*(z - 1)) / (resonance*(z - 1));
	//calculate filtered signal
	x = x + (input - y)*c;
	y = y + x;
	x = x*r;
	output = y;
		
	return(output);

}

double JackFilter::highPass(double input, double cutoff, double resonance)
{
	// high pass filtering is essentially the same algorithm as a low pass with negated ouput values 
	double y = lowPass(input, cutoff, resonance);
	output = input - y;
	return(output);
}


