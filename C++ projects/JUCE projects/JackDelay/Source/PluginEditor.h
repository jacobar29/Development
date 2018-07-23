/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class JackDelayAudioProcessorEditor  : public AudioProcessorEditor
{
public:
	JackDelayAudioProcessorEditor(JackDelayAudioProcessor&);
    ~JackDelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
	JackDelayAudioProcessor& processor;

	Slider delayTime;
	Slider decayTime;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayVal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JackDelayAudioProcessorEditor)
};
