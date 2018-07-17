/*
  ==============================================================================

    Envelope.h
    Created: 14 Jul 2018 1:35:18pm
    Author:  J

  ==============================================================================
*/

#pragma once

class JackEnv
{
public:
	void setSampleRate(double sampRate);
	void setAttack(double attackMS);
	void setRelease(double releaseMS);
	void setDecay(double decayMS);
	void setSustain(double sustainL);

	double adsr(double input, int trigger);
	int trigger;
private:
	double sampleRate = 44100;

	double output;

	double attack;
	double decay;
	double sustainLevel;
	double release;
	double amplitude;

	//int trigger;
	long holdtime = 1;
	long sustainCount;
	bool attacking;
	bool decaying;
	bool sustaining;
	bool releasing;



}
;
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