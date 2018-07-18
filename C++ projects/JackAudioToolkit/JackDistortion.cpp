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

float JackDistortion::fuzz(float input, float threshold, float gate)
{
	
	signal = input;
	if ((signal < gate  && signal > 0) || (signal < 0 && signal > -gate))// if signal is between gate and negative gate
		return signal;
	if (signal > 0)
		signal = threshold - exp(-signal);
	else if (signal < 0)
		signal = threshold + exp(signal);
	return signal;


}
	  // fuzz - flip values and throttle threshold range, last 20% sounds good but the rest is too much,