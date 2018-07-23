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

	float process(float inputSample, float decay, int delay);

private:
	float sampleRate;
	float output;
	
	int delayTime;
	int delayLength;

	std::vector<float> buffCopy; 
	int writePointer;
	int readPointer;
	int bufferLength;

};