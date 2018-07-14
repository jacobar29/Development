/*
==============================================================================

Oscillator.cpp
Created: 14 Jul 2018 9:17:02am
Author:  J

==============================================================================
*/

#include "JackOsc.h"

#include <math.h>
#include <stdlib.h>

JackOsc::JackOsc()
{
	phase = 0.0;
	//square wave stuff
	n = 0;
	out = 1;
	setSampleRate(44100);


}
JackOsc::~JackOsc()
{

}

void JackOsc::setSampleRate(int sampRate)
{
	sampleRate = sampRate;

}

int JackOsc::getSampleRate()
{
	return sampleRate;
}

float JackOsc::sinewave(float frequency)
{
	advancePhase(frequency);
	return sin(phase*(2 * M_PI));


}

float JackOsc::squareWave(float frequency)
{

	int N = sampleRate / (2 * frequency);

	if ((n++) % N == 0)
		out *= -1; // this will toggle, -1,+1,-1,+1...

	return out;

}

float JackOsc::triangleWave(float frequency)
{

	advancePhase(frequency);
	return 1 - fabs(phase - 0.5) * 4;

}

float JackOsc::sawWave(float frequency)
{
	advancePhase(frequency);
	return phase * 2 - 1;

}

float JackOsc::whiteNoise()
{

	double temp;
	double noiseVal;
	double result;
	int p;

	p = 1;

	while (p > 0)
	{
		noiseVal = (rand() / ((double)RAND_MAX));

		if (noiseVal == 0)
		{// noiseVal is >= (RAND_MAX / 2)
			p = 1;
		}
		else
		{
			p = -1;
		}

	}

	temp = cos((2.0 * (double)M_PI) * rand() / ((double)RAND_MAX));
	result = sqrt(-2.0 * log(noiseVal)) * temp;

	return result;
}

void JackOsc::advancePhase(float frequency)
{

	if (phase >= 1.0)
		phase -= 1.0;
	phase += (1. / (sampleRate / frequency));

}