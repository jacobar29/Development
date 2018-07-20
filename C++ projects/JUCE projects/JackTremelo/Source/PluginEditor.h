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
class JackTremeloAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    JackTremeloAudioProcessorEditor (JackTremeloAudioProcessor&);
    ~JackTremeloAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
	// This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JackTremeloAudioProcessor& processor;
	// GUI components
	Slider rateSlider;
	Slider depthSlider;


	// atachments to link GUI components to the value tree	
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> rateVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> depthVal;
    
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JackTremeloAudioProcessorEditor)
};
