/*
  ==============================================================================

    Oscillator.cpp
    Created: 13 Jul 2018 4:46:45pm
    Author:  J

  ==============================================================================
*/

#include "Oscillator.h"
#include <math.h>
#include <stdlib.h>

Oscillator::Oscillator()
{
	phase = 0.0;
	//square wave stuff
	n = 0;
	out = 1;
	
}
Oscillator::~Oscillator()
{

}

void Oscillator::setSampleRate(int sampRate)
{
	sampleRate = sampRate;

}

int Oscillator::getSampleRate()
{
	return sampleRate;
}

float Oscillator::sinewave(float frequency)
{
	advancePhase(frequency);
	return sin(phase*(2 * M_PI));


}

float Oscillator::squareWave(float frequency)
{
	
	int N = sampleRate / (2 * frequency);
		
	if ((n++) % N == 0)
		out *= -1; // this will toggle, -1,+1,-1,+1...

	return out;

}

float Oscillator::triangleWave(float frequency)
{

	advancePhase(frequency);
	return 1 - fabs(phase - 0.5) * 4;

}													   

float Oscillator::sawWave(float frequency)
{
	advancePhase(frequency);
	return phase * 2 - 1;

}

float Oscillator::whiteNoise()
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

void Oscillator::advancePhase(float frequency)
{

	if (phase >= 1.0)
		phase -= 1.0;
	phase += (1. / (sampleRate / frequency));

}