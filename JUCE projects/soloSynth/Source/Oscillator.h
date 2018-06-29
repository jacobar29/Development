/*
  ==============================================================================

    Oscillator.h
    Created: 23 May 2018 10:28:13am
    Author:  J

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Oscillator    : public Component
{
public:
    Oscillator(SoloSynthAudioProcessor&, std::string);
    ~Oscillator();
					  
    void paint (Graphics&) override;
    void resized() override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	SoloSynthAudioProcessor& processor;

	// ===== GUI elements ======
	ComboBox oscMenu;
	Slider gainSlider;
	Slider freqSlider;

	// === control attachments ====
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveType;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> freqShiftVal;

	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
