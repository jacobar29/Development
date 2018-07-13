/*
  ==============================================================================

    Oscillator.h
    Created: 13 Jul 2018 4:46:45pm
    Author:  J

  ==============================================================================
*/


#pragma once

# define M_PI 3.14159265358979323846  // value of pi


class Oscillator {

public:
	Oscillator();
	~Oscillator();

	void setSampleRate(int SampleRate);
	int getSampleRate();
	float sinewave(float frequency);

private:
	float phase; 
	float sampleRate = 44100;



};