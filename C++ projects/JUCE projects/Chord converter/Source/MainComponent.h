/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public Component, public  Slider::Listener, Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void getInputText();

	void sliderValueChanged(Slider* slider) override;
	void buttonClicked(Button* button) override;

private:
	// GUI Elements
	juce::TextEditor input;
	juce::TextEditor output;
	juce::Slider transSlider;
	juce::Label inL;
	juce::Label outL;
	juce::Label sL;
	juce::TextButton clear;

	//represents a standard octave
	std::string chords[12] = { "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#" };

	std::vector <std::string> inputChords;
	std::string chord;
	std::string temp;

	std::string outString;
	std::string baseNote;
	std::string noteSuffix;

	int noteIndex;
	int newNoteIndex;
	int modifier;
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
