/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JackTremeloAudioProcessorEditor::JackTremeloAudioProcessorEditor (JackTremeloAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	// set the appearance of GUI elements
    setSize (400, 300);

	rateSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	rateSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(rateSlider);
	
	depthSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	depthSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(depthSlider);

	rateVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "rate", rateSlider);
	depthVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "depth", depthSlider);
	
}

JackTremeloAudioProcessorEditor::~JackTremeloAudioProcessorEditor()
{
}

//==============================================================================
void JackTremeloAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
	//draw labels
	juce::Rectangle<int> labels = getLocalBounds();
	g.drawText("Rate", labels.removeFromLeft(labels.getWidth() / 2), Justification::centred, true);
	g.drawText("depth", labels, Justification::centred, true);
	
	
}

void JackTremeloAudioProcessorEditor::resized()
{

	juce::Rectangle<int> area = getLocalBounds();

	
	rateSlider.setBounds(area.removeFromLeft(area.getWidth() / 2));
	depthSlider.setBounds(area);
	
	
}

