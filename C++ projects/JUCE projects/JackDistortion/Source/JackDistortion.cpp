/*
  ==============================================================================

    JackDistortion.cpp
    Created: 17 Jul 2018 4:05:11pm
    Author:  J

  ==============================================================================
*/

#include "JackDistortion.h"
#include <math.h>

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

float JackDistortion::fuzz(float input, float threshold)
{
	if (threshold > 1)
		threshold = 1;
	signal = input;
	float distSignal;
	float gate = 0.01;
	if (signal > gate)
		distSignal = threshold - exp(-signal);
	else if (signal < -gate)
		distSignal = threshold + exp(signal);
	distSignal = (signal + (distSignal * threshold));
	return distSignal * 1;

}
	  // fuzz - flip values and throttle threshold range, last 20% sounds good but the rest is too much,