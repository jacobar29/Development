/*
==============================================================================

Panner.h
Created: 13 Jul 2018 4:46:45pm
Author:  J

==============================================================================
*/


#pragma once

# define M_PI 3.14159265358979323846  // value of pi


class Panner {

public:

	void prepareToPlay(int SampleRate);
	float process(int waveChoice, float frequency);
	void advancePhase(float frequncy);
	float sineWave(float frequency);
	float squareWave(float frequency);
	float triangleWave(float frequency);



private:
	float phase;
	float sampleRate = 44100;

	//square wave values
	int n;
	int out;



};