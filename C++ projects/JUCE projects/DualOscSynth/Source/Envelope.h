/*
  ==============================================================================

    Envelope.h
    Created: 23 May 2018 10:27:54am
    Author:  J

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Envelope    : public Component 
					
{
public:
    Envelope(DualOscSynthAudioProcessor&, std::string);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

private:
	DualOscSynthAudioProcessor& processor;
	//=================== osc2 ==================================================

	Slider attackSlider;
	Slider decaySlider;
	Slider sustainSlider;
	Slider releaseSlider;
	Label aLabel;
	Label dLabel;
	Label sLabel;
	Label rLabel;
   	
	// === control attachments ====
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseVal;
	


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
