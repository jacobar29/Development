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
	for (int i = 0; i <= sampleRate; i++)
	{
		buffCopy.push_back(0.0);


	}
	// lengths for each buffer
	revBuffLength = 2 * sampleRate;
	delayLength = sampleRate;

	for (int i = 0; i < revBuffLength + 1; i++)
		revBuff.push_back(0.0);
	
	delayTime = sampleRate * 0.5; // initialise delaytime at 0.5sec
	shiftReadPointer = delayLength - delayTime;  // start position for read pointer

	// read pointer for reverse buffer
	revPointer = revBuffLength;
	
	revWritePointer = 0;// place read pointer behind write by delaySamples;
	// counter used in pitch stretching
	counter = 0;
}
//ToDo replace all function params with a param array
		// add revBuffer and delay buffer length control, adjust all pointer looping to work with this
		// tweak shift control, remove values that are not producing much change
		// labels for the level controls
		// posisble filtering, particularly low pass for the shifted signal
		
float JackDelay::process(float inputSample, float decay, int delay, int shiftFactor, float revLevel, float delayLevel, float shiftLevel, float dryLevel)
{
	// adjust range between read and write pointer
	delayPointer = writePointer + delay;
	
	if (delayPointer > delayLength)
		delayPointer -= delayLength;
    // reverse pointer iterates backwards through buffer, fixed iteration rate
	revPointer --;
	
	if (revPointer < 0)
		revPointer = revBuffLength;
	// shouldnt happen but just in case
	if (revPointer > revBuffLength)
		revPointer = 0;
	// case where pitch shifted upwards
	if (shiftFactor >= 0)
		shiftPointer += shiftFactor;
	//case where pitch shifted down, quick and dirty method, samples are repeated a certain number of times
	else {
		if (counter != shiftFactor)
			counter--;
		if (counter == shiftFactor)
		{
			shiftPointer ++;
			counter = 0;
		}
	}
	// loop shift pointer
	if (shiftPointer >= delayLength)
		shiftPointer -= delayLength;	
	//shouldnt happen butjust in case
	if (shiftPointer < 0)
		shiftPointer = 0;
	// calculate level of each value
	float revValue = (revBuff[revPointer] * revLevel) * decay;
	float delayValue = (buffCopy[delayPointer] * delayLevel) * decay;
	float shiftValue = (buffCopy[shiftPointer] * shiftLevel) * decay;
	float dryValue = inputSample * dryLevel; // not written to buffer
	

	// dryValue is not passed to output until after it has been written so that it functions as a rudimentary bypass
	output =  revValue + delayValue + shiftValue; 

   

	// quick and dirty level cap to stop delay line running away and overloading the system audio.
	if (output > 1)
		output = 1.0;
	// copy new values to buffer
	buffCopy[writePointer] = output + inputSample;
	// add scaled dry value to output
	output += dryValue; 
	//copy input to reverse buffer
	revBuff[revWritePointer] = inputSample;
	// increment write pointers. these must iterate at a fixed rate
	writePointer++;
	revWritePointer++;
	if (writePointer > delayLength)
		writePointer = 0;
	
	if (revWritePointer > revBuffLength)
		revWritePointer = 0;
	// again shouldnt happen but just in case
	if (revWritePointer < 0)
		revWritePointer = revBuffLength;
	
	return output;

}
