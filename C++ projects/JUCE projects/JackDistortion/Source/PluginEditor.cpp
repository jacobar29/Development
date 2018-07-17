/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JackDistortionAudioProcessorEditor::JackDistortionAudioProcessorEditor (JackDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
	addAndMakeVisible(gainSlider);
	gainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	gainSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

	addAndMakeVisible(thresholdSlider);
	thresholdSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	thresholdSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

	addAndMakeVisible(volumeSlider);
	volumeSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	volumeSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
   
	StringArray menuItems("Symmetrical", "Asymmetrical", "fuzz");
	distMenu.addItemList(menuItems, 1);
	distMenu.setJustificationType(Justification::centred);
	addAndMakeVisible(distMenu);
	
	thresholdVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "threshold", thresholdSlider);
	distType = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "distType", distMenu);
	volumeVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "volume", volumeSlider);
	gainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "inputGain", gainSlider);


}

JackDistortionAudioProcessorEditor::~JackDistortionAudioProcessorEditor()
{
}

//==============================================================================
void JackDistortionAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);

}

void JackDistortionAudioProcessorEditor::resized()
{
	juce::Rectangle<int> area = getLocalBounds();
	juce::Rectangle<int> dialArea(10, 40, area.getWidth() - 10, area.getHeight() - 10);
	distMenu.setBounds(area.removeFromTop(30));
	gainSlider.setBounds(area.removeFromLeft(area.getWidth() / 3));
	thresholdSlider.setBounds(area.removeFromLeft(area.getWidth() /2));
	volumeSlider.setBounds(area);

}
