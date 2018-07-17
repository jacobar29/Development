/*
  ==============================================================================

    JackFilter.h
    Created: 14 Jul 2018
    Author:  Jack Barnes

  ==============================================================================
*/

#pragma once

class JackFilter {

public:
	JackFilter();
	JackFilter(double sampleRateHz);
	void setSampleRate(double newSampleRate);

	double cutoff;

	double resonance;

	double bandPass(double input, double cutoff1, double resonance);

	double lowPass(double input, double cutoff, double resonance);
	
	double highPass(double input, double cutoff, double resonance);

private:
	double sampleRate;
	double gain;

	double input;
	
	double output;
	
	double inputs[10];
	
	double outputs[10];
	
	double cutoff1;
	
	double x;//speed

	double y;//pos
	
	double z; // poles
	
	double c;//filter coefficient

};