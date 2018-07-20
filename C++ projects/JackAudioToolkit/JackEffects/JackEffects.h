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