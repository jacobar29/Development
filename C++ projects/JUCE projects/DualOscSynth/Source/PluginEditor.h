/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "OscGui.h"


//==============================================================================

class DualOscSynthAudioProcessorEditor  : public AudioProcessorEditor,
	public MidiKeyboardStateListener
{
public:
    DualOscSynthAudioProcessorEditor (DualOscSynthAudioProcessor&);
    ~DualOscSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	
	// onscreen keyboard pure virtual functions
	void handleNoteOn(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override;
	void handleNoteOff(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DualOscSynthAudioProcessor& processor;

	Synthesiser& mySynth;

	OscGui osc1Gui;
	OscGui osc2Gui;

	// things for the onscreen keyboard	
	juce::MidiKeyboardState state;
	juce::MidiKeyboardComponent keys;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DualOscSynthAudioProcessorEditor)
};
