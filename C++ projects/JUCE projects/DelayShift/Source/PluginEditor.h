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
class DelayShiftAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DelayShiftAudioProcessorEditor (DelayShiftAudioProcessor&);
    ~DelayShiftAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DelayShiftAudioProcessor& processor;


	Slider delayTime;
	Slider decayTime;
	Slider shiftSlider;

	Slider revLevelSlider;
	Slider delayLevelSlider;
	Slider shiftLevelSlider;
	Slider dryLevelSlider;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> shiftVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayVal;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> revLevelVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayLevelVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> shiftLevelVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dryLevelVal;

	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayShiftAudioProcessorEditor)
};
