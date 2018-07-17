/*
  ==============================================================================

    JackFilter.cpp
    Created: 14 Jul 2018
    Author:  Jack Barnes

  ==============================================================================
*/

#include "JackFilter.h"
#include <math.h>


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


