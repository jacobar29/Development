/*
  ==============================================================================

    Filter.h
    Created: 23 May 2018 10:28:03am
    Author:  J

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(SoloSynthAudioProcessor&, std::string);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:
	SoloSynthAudioProcessor& processor;

	//=================== osc1 ==================================================

	// ===== GUI elements ======
	Slider filterCutoff;
	Slider filterRes;
	ComboBox filterMenu;

	// === control attachments ====
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resVal;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
