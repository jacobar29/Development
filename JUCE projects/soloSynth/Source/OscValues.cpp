/*
  ==============================================================================

    OscRow.cpp
    Created: 19 Jun 2018 12:01:19pm
    Author:  J

  ==============================================================================
*/

#include "OscValues.h"
OscValues::OscValues(){}

OscValues::OscValues(AudioProcessorValueTreeState& valueTree, std::string oscName)
{
	name = oscName;
	tree = &valueTree;
	// Create normalisable ranges for each parameter to be controlled, optional third argument sets step size
	// add Parameters to the processor's value tree, these can be easily accessed from wherever needed
	NormalisableRange<float> waveParam(0, 2);
	NormalisableRange<float> gainParam(0.0, 1.0f, 0.1f);
	NormalisableRange<float> freqShiftParam(-12.0f, 12.0f, 1.0f);

	NormalisableRange<float> lfoStateParam(0.0f, 3.0f, 1.0f);
	NormalisableRange<float> lfoDepthParam(0.1, 1.0f, 0.1f);
	NormalisableRange<float> lfoRateParam(0.1, 3.0f, 0.1f);

	NormalisableRange<float> attackParam(0.1f, 10000.0f, 0.1f);
	NormalisableRange<float> decayParam(0.1f, 2000.0f, 0.1f);
	NormalisableRange<float> sustainParam(0.0f, 1.0f, 0.1f);
	NormalisableRange<float> releaseParam(0.1f, 5000.0f, 0.1f);

	NormalisableRange<float> filterCutoffVal(20.0f, 9000.0f, 1.0f, 0.5);
	NormalisableRange<float> fitlerResVal(1, 5, 0.1);
	NormalisableRange<float> filterTypeVal(0, 2);

	std::string nameUpper = name;
	nameUpper[0] = toupper(nameUpper[0]);
	
	// ========= Oscillator ========================================================
 	tree->createAndAddParameter(std::string(name + "WaveType"), std::string(nameUpper +"WaveType"), std::string(name + "WaveType"), waveParam, 0, nullptr, nullptr);
	tree->createAndAddParameter(std::string(name + "Gain"), std::string(nameUpper + "Gain"), std::string(name + "Gain"), gainParam, 0.5f, nullptr, nullptr);
	tree->createAndAddParameter(std::string(name + "FreqShiftVal"), std::string(nameUpper + "FreqShiftVal"), std::string(name + "FreqShiftVal"), freqShiftParam, 0, nullptr, nullptr);

	//======= LFO ==================================================================
	tree->createAndAddParameter(std::string(name +"LfoState"), std::string(nameUpper + "LfoState"), std::string(name + "LfoState"), lfoStateParam, 0.0f, nullptr, nullptr);
	tree->createAndAddParameter(std::string(name + "LfoDepth"), std::string(nameUpper + "LfoDepth"), std::string(name + "LfoDepth"), lfoDepthParam, 0.0f, nullptr, nullptr);
	tree->createAndAddParameter(std::string(name + "LfoSpeed"), std::string(nameUpper + "LfoSpeed"), std::string(name + "LfoSpeed"), lfoRateParam, 0.0f, nullptr, nullptr);

	//=========    Envelope    =====================================================
	tree->createAndAddParameter(std::string(name + "Attack"), std::string(nameUpper + "Attack"), std::string(name + "Attack"), attackParam, 0.1f, nullptr, nullptr);
	tree->createAndAddParameter(std::string(name + "Decay"), std::string(nameUpper + "Decay"), std::string(name + "Decay"), decayParam, 0.1f, nullptr, nullptr);
	tree->createAndAddParameter(std::string(name + "Sustain"), std::string(nameUpper + "Sustain"), std::string(name + "Sustain"), sustainParam, 0.8f, nullptr, nullptr);
	tree->createAndAddParameter(std::string(name + "Release"), std::string(nameUpper + "Release"), std::string(name + "Release"), releaseParam, 0.1f, nullptr, nullptr);

	//========   Filter     ================================================
	tree->createAndAddParameter(std::string(name + "FilterCutoffVal"), std::string(nameUpper + "FilterCutoffVal"), std::string(name + "FilterCutoffVal"), filterCutoffVal, 400, nullptr, nullptr);
	tree->createAndAddParameter(std::string(name + "FilterResVal"), std::string(nameUpper + "FilterResVal"), std::string(name + "FilterResVal"), fitlerResVal, 1.0f, nullptr, nullptr);	tree->createAndAddParameter(std::string(name + "FilterTypeVal"), std::string(nameUpper + "FilterTypeVal"), std::string(name + "FilterTypeVal"), filterTypeVal, 0, nullptr, nullptr);
	
}





