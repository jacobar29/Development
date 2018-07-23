/*
  ==============================================================================

    Jack Delay.cpp
    Created: 23 Jul 2018 9:25:51am
    Author:  J

  ==============================================================================
*/

#include "JackDelay.h"


void JackDelay::prepareToPlay(int sampRate)
{
	sampleRate = sampRate;
	writePointer = 0;
	for (int i = 0; i <= sampleRate ; i++)
		buffCopy.push_back(0.0);
	delayTime = sampleRate * 0.5; // initialise delaytime at 0.5sec
	delayLength = sampleRate;
	readPointer = delayLength - delayTime;	 // place read pointer behind write by delaySamples;

}

float JackDelay::process(float inputSample, float decay, int delay)
{
	// adjust range between read and write pointer
	readPointer = writePointer + delay;
	
	//loop readpointer if larger than buffer
	if (readPointer > delayLength)
		readPointer -= delayLength;

	output =inputSample + buffCopy[readPointer] * decay; // output = read pointer plus the scaled output value
	buffCopy[writePointer] = output; // copy new values to buffer,
	
	writePointer++;
	if (writePointer > delayLength)
		writePointer = 0;

	return output;

}
