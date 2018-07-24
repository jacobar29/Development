/*
  ==============================================================================

    JackDelay.h
    Created: 23 Jul 2018 9:25:51am
    Author:  J

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class JackDelay {
public:
	
	void prepareToPlay(int sampleRate);

	float process(float inputSample, float decay, int delay, int shiftFactor, float revLevel, float delayLevel, float shiftLevel, float dryLevel);

private:
	int counter;

	float sampleRate;
	float output;
	
	int delayTime;

	int delayLength;
	int revBuffLength;
	int revWritePointer;
	std::vector<float> buffCopy;
	std::vector<float> revBuff;

	


	int writePointer;
	
	int delayPointer;
	float delayVal;
	int revPointer;
	float revVal;

	int shiftReadPointer;
	float shiftPointer;

	int bufferLength;

};