/*
  ==============================================================================

    Oscillator.h
    Created: 23 May 2018 10:28:13am
    Author:  J

  ==============================================================================
*/

#pragma once

# define M_PI 3.14159265358979323846  // value of pi


class JackOsc {

public:
	JackOsc();
	~JackOsc();

	void setSampleRate(int SampleRate);
	int getSampleRate();
	float sinewave(float frequency);
	float squareWave(float frequency);
	float triangleWave(float frequency);
	float sawWave(float frequency);
	float whiteNoise();


	void advancePhase(float frequncy);

private:
	float phase;
	float sampleRate = 44100;

	//square wave values
	int n;
	int out;

};
