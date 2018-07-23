/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JackDelayAudioProcessorEditor::JackDelayAudioProcessorEditor(JackDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	delayTime.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	delayTime.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(delayTime);

	decayTime.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	decayTime.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(decayTime);

	
	delayVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "delayTime", delayTime);
	decayVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decayTime);

}

JackDelayAudioProcessorEditor::~JackDelayAudioProcessorEditor()
{
}

//==============================================================================
void JackDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
	juce::Rectangle<int> labels = getLocalBounds();
	g.drawText("Delay Time", labels.removeFromLeft(labels.getWidth() / 2), Justification::centred, true);
	g.drawText("Decay Time", labels, Justification::centred, true);

}

void JackDelayAudioProcessorEditor::resized()
{
	juce::Rectangle<int> area = getLocalBounds();


	delayTime.setBounds(area.removeFromLeft(area.getWidth() / 2));
	decayTime.setBounds(area);
}
