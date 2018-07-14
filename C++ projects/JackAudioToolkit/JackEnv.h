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