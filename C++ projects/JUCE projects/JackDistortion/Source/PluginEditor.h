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
class JackDistortionAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    JackDistortionAudioProcessorEditor (JackDistortionAudioProcessor&);
    ~JackDistortionAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
	
	Slider gainSlider;
	Slider volumeSlider;
	Slider thresholdSlider;
	ComboBox distMenu;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> thresholdVal;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> distType;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> volumeVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainVal;



    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JackDistortionAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JackDistortionAudioProcessorEditor)
};
