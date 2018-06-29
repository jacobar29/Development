/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SoloSynthAudioProcessorEditor::SoloSynthAudioProcessorEditor(SoloSynthAudioProcessor& p)
					: AudioProcessorEditor(&p), processor(p),					 osc1Gui(p, "osc1"), osc2Gui(p, "osc2"),					 keys(state, MidiKeyboardComponent::Orientation::horizontalKeyboard), mySynth(p.mySynth){

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

SoloSynthAudioProcessorEditor::~SoloSynthAudioProcessorEditor()
{
}

//==============================================================================
void SoloSynthAudioProcessorEditor::paint (Graphics& g)
{
	// fill background colour
	g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
   
}

void SoloSynthAudioProcessorEditor::resized()
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
void SoloSynthAudioProcessorEditor::handleNoteOn(MidiKeyboardState* source,
	int midiChannel, int midiNoteNumber, float velocity)
{											   
	mySynth.noteOn(midiChannel, midiNoteNumber, velocity);

}

void SoloSynthAudioProcessorEditor::handleNoteOff(MidiKeyboardState* source,
	int midiChannel, int midiNoteNumber, float velocity)
{
	mySynth.noteOff(midiChannel, midiNoteNumber, velocity, true);

}
