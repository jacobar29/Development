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
class PanneramaAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    PanneramaAudioProcessorEditor (PanneramaAudioProcessor&);
    ~PanneramaAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PanneramaAudioProcessor& processor;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> rateVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> widthVal;


	Slider rateSlider;
	Slider widthSlider;

	Label rL;
	Label wL;


	juce::Rectangle<int> area;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanneramaAudioProcessorEditor)
};
