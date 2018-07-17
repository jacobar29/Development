/*
  ==============================================================================

    JackDistortion.h
    Created: 17 Jul 2018 4:05:11pm
    Author:  J

  ==============================================================================
*/

#pragma once

class JackDistortion {
public:
	float clipSym(float input, float threshold); // symetrical clipping
	float clipAsym(float input, float threshold); // a symetrical clipping
	float fuzz(float input, float threshold);
private:
	float signal; // input signal
	float negThreshold; // negative value of threshold

};
