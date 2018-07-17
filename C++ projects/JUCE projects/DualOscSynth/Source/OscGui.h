/*
==============================================================================

OscGui.h
Created: 19 Jun 2018 5:12:11pm
Author:  J

==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Envelope.h"
#include "Oscillator.h"
#include "Filter.h"
#include "Lfo.h"

//==============================================================================
/*
*/
class OscGui : public Component
{
public:
	OscGui(DualOscSynthAudioProcessor&, std::string);
	~OscGui();

	void paint(Graphics&) override;
	void resized() override;

private:
	DualOscSynthAudioProcessor& processor;

	Oscillator oscGui;
	Lfo lfoGui;
	Envelope envGui;
	Filter filterGui;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscGui)
};
