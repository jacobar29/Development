/*
  ==============================================================================

    JackEffects.h
    Created: 20 Jul 2018 8:23:00am
    Author:  Jack Barnes

  ==============================================================================
*/

#pragma once

class JackTremelo
{
public:
	//initialse required values
	void prepareToPlay(float sapleRate);
	
	float process(float inputSample, float rate, float depth);

private:
	float sampleRate;
	float phase;

};

//=====================================================================


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