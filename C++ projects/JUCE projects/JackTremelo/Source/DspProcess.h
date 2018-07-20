/*
  ==============================================================================

    DspProcess.h
    Created: 20 Jul 2018 8:23:00am
    Author:  Jack Barnes

  ==============================================================================
*/

#pragma once

class DspProcess
{
public:
	void prepareToPlay(float sampleRate);
	float process(float currentSample, float SliderVal, float depth);
private:
	float sampleRate;
	float phase;

};