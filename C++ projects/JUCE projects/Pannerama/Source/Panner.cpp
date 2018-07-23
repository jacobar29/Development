/*
==============================================================================

Oscillator.cpp
Created: 13 Jul 2018 4:46:45pm
Author:  J

==============================================================================
*/

#include "Panner.h"
#include <math.h>
#include <stdlib.h>


// initialise required values 
void Panner::prepareToPlay(int sampRate)
{
	sampleRate = sampRate;
	phase = 0.0;
	n = 0;
	out = 1;
}


float Panner::process(int waveChoice, float frequency)
{

	float wave;
	float output;
	switch (waveChoice)
	{									 // offset these vals
	case 0: wave = sineWave(frequency);
		break;
	case 1:	wave = squareWave(frequency);
		break;
	case 2: wave = triangleWave(frequency);
		break;
	default: wave = sineWave(frequency);
	}
	wave = (wave + 1) / 2; // offset values

	// care amounts are inversely proportional
	//
	return wave;
}

float Panner::sineWave(float frequency)
{
	float out = sin(phase * (2 * M_PI));
	advancePhase(frequency);
	return out;
}

float Panner::squareWave(float frequency)
{
	int N = sampleRate / (2 * frequency);

	if ((n++) % N == 0)
		out *= -1; // this will toggle, -1,+1,-1,+1...

	return out;

}

float Panner::triangleWave(float frequency)
{
	float out = 1 - fabs(phase - 0.5) * 4;
	advancePhase(frequency);
	return out;

}


void Panner::advancePhase(float frequency)
{

	if (phase >= 1.0)
		phase -= 1.0;
	phase += (1. / (sampleRate / frequency));

}