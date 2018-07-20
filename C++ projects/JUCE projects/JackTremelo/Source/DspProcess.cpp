/*
  ==============================================================================

    DspProcess.cpp
    Created: 20 Jul 2018 8:23:00am
    Author:  J

  ==============================================================================
*/

#include "DspProcess.h"
#include <math.h>
# define TWOPI 2* 3.14159265358979323846  // 2 * value of pi


float DspProcess::process(float currentSample, float rate, float depth)
{
	
	float wave = ((sin(phase*(TWOPI)) + 1)* 0.5) * depth; // produce an offset sinewave oscillating between 0 and 1
	//advance phase
	if (phase >= 1.0) 
		phase -= 1.0;
	phase += (1. / (sampleRate / rate));
	
	// addition of a portion of the original wave produces the illusion of depth
	return (wave * currentSample ) + ((1 -depth) * currentSample);
  
}
void DspProcess::prepareToPlay(float sampRate)	
{
	phase = 0.0;
	sampleRate = sampRate;
}
