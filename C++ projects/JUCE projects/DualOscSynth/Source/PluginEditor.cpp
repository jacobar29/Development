/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "../Source/PluginProcessor.h"

//==============================================================================
DualOscSynthAudioProcessorEditor::DualOscSynthAudioProcessorEditor (DualOscSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), osc1Gui(p, "osc1"), osc2Gui(p, "osc2"),	keys(state, MidiKeyboardComponent::Orientation::horizontalKeyboard), mySynth(p.mySynth)
{
   setSize (750, 500);	// window size
	//=== oscillators ===
	addAndMakeVisible(osc1Gui);
	addAndMakeVisible(osc2Gui);
		
	// keyboard and listener
	addAndMakeVisible(keys);
	state.addListener(this);
	keys.setAvailableRange(48 , 84);
	keys.setKeyWidth(690 / 21);
	keys.setBlackNoteLengthProportion(0.5);
}

DualOscSynthAudioProcessorEditor::~DualOscSynthAudioProcessorEditor()
{
}

//==============================================================================
void DualOscSynthAudioProcessorEditor::paint (Graphics& g)
{

	// fill background colour
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void DualOscSynthAudioProcessorEditor::resized()
{
	juce::Rectangle<int> area = getLocalBounds();

	// ==== midi keyboard ===
	int keyboardHeight = 80;
	juce::Rectangle<int> keyArea(30, area.getHeight() - keyboardHeight, area.getWidth() - 60, keyboardHeight);
	keys.setBounds(keyArea);

	// === oscs ===
	int oscHeight = 200;
	osc1Gui.setBounds(area.removeFromTop(oscHeight));
	osc2Gui.setBounds(area.removeFromTop(oscHeight));
}

// midikeyboard note handlers
void DualOscSynthAudioProcessorEditor::handleNoteOn(MidiKeyboardState* source,
	int midiChannel, int midiNoteNumber, float velocity)
{
	mySynth.noteOn(midiChannel, midiNoteNumber, velocity);

}

void DualOscSynthAudioProcessorEditor::handleNoteOff(MidiKeyboardState* source,
	int midiChannel, int midiNoteNumber, float velocity)
{
	mySynth.noteOff(midiChannel, midiNoteNumber, velocity, true);

}