/*
  ==============================================================================

    JackEffects.cpp
    Created: 20 Jul 2018 8:23:00am
    Author:  Jack Barnes

  ==============================================================================
*/

#include "JackEffects.h"
#include <math.h>

# define TWOPI 2* 3.14159265358979323846  // 2 * value of pi

// a tremelo modulates the amplitude of the input signal with a sinewave. the sinewave algorithm is identical to the JackOsc::offsetSineWave() function

float JackTremelo::process(float inputSample, float rate, float depth)
{
	
	float wave = ((sin(phase*(TWOPI)) + 1)* 0.5) * depth; // produce an offset sinewave oscillating between 0 and 1

	//advance phase
	if (phase >= 1.0)
 
		phase -= 1.0;

	phase += (1. / (sampleRate / rate));
	
// addition of a portion of the original wave produces the illusion of depth

	return (wave * inputSample ) + ((1 -depth) * inputSample);
  
}

void JackTremelo::prepareToPlay(float sampRate)	
{
	phase = 0.0;
	sampleRate = sampRate;
}
