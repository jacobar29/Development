/*
  ==============================================================================

    Oscillator.cpp
    Created: 13 Jul 2018 4:46:45pm
    Author:  J

  ==============================================================================
*/

#include "Oscillator.h"
#include <math.h>

Oscillator::Oscillator()
{
	phase = 0.0;
	
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
	if (phase >= 1.0) phase -= 1.0;
	phase += (1. / (sampleRate / frequency));
	return sin(phase*(2 * M_PI));

}
