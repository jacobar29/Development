/*
  ==============================================================================

    Lfo.h
    Created: 5 Jun 2018 4:20:01pm
    Author:  J

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Lfo    : public Component	
			
{
public:
    Lfo(DualOscSynthAudioProcessor&, std::string name);
    ~Lfo();
  
	void paint (Graphics&) override;
    void resized() override;

private:
	DualOscSynthAudioProcessor& processor;
	
	// ===== GUI elements ======
	ComboBox lfoMenu;
	Slider modDepthSlider;
	Slider modRateSlider;
	
	// === control attachments ====
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> lfoState;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> modDepth;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> modRate;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Lfo)
};
