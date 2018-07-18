/*
  ==============================================================================

    JackDistortion.cpp
    Created: 17 Jul 2018 4:05:11pm
    Author:  J

  ==============================================================================
*/

#include "JackDistortion.h"
#include <math.h> 

# define M_PI 3.14159265358979323846  // value of pi

float JackDistortion::clipSym(float input, float threshold)
{
	signal = input;
	negThreshold = 0 - threshold;

	if (signal > threshold)
		signal =  threshold;
	else if (signal < negThreshold)
		signal = negThreshold;
	return signal;
}

float JackDistortion::clipAsym(float input, float threshold)
{
	signal = input;
 	if (signal > threshold)
		signal = threshold;
	return signal;
}
	// fuzz is VERY MESSY and values below the gate are almost entirely lost, 
	//the gate is intended to eliminate screaming feedback from signal noise,this can be really cool so it isnt hardcoded (0.01 is enough for most cases) but is far from pleasent
	// gate values of 0.01 - 0.1 work well
float JackDistortion::fuzz(float input, float threshold, float gate = 0.01)
{
	
	signal = input;
	// if signal is between gate and negative gate
	if ((signal < gate  && signal > 0) || (signal < 0 && signal > -gate))
		return signal;

	if (signal > 0)
		signal = threshold - exp(-signal);
	
	else if (signal < 0)
		signal = threshold + exp(signal);

	return signal;

}
