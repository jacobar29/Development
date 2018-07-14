/*
  ==============================================================================

    OscRow.h
    Created: 19 Jun 2018 11:17:57am
    Author:  J

  ==============================================================================
*/
// this component creates and adds the required parameters to the audioprocessor's value tree
// all parameters are named using the string given in the constructor plus the parameters name



#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
//==============================================================================


class OscValues
{
public:
	OscValues();
	OscValues(AudioProcessorValueTreeState&, std::string);


private:
	std::string name;
	AudioProcessorValueTreeState* tree;

	

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscValues)
};
