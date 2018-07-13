/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PanneramaAudioProcessorEditor::PanneramaAudioProcessorEditor (PanneramaAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    
    setSize (400, 300);
	// rate slider and label
	rL.setText("Pan Rate", dontSendNotification);
	rL.attachToComponent(&rateSlider, false);
	rL.setJustificationType(Justification::centred);
	addAndMakeVisible(rL);
	
	rateSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	rateSlider.setTextBoxStyle(Slider::TextBoxBelow, false,50,20);
	addAndMakeVisible(rateSlider);
	
	// width slider and label
	wL.setText("Pan Width", dontSendNotification);
	wL.attachToComponent(&widthSlider, false);
	wL.setJustificationType(Justification::centred);
	addAndMakeVisible(wL);

	widthSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	widthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
	addAndMakeVisible(widthSlider);

	// create slider attachments, linking sliders to their corresponding valuetree parameters
	rateVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "panRate", rateSlider);
	widthVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "panWidth", widthSlider);
}

PanneramaAudioProcessorEditor::~PanneramaAudioProcessorEditor()
{
}

//==============================================================================
void PanneramaAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
	juce::Rectangle<int> labelArea(0, 0, area.getWidth(), 50);
    g.setColour (Colours::white);
    g.setFont (15.0f);
}

void PanneramaAudioProcessorEditor::resized()
{
	area = getLocalBounds();
	// add GUI elements to layout by removing from rectangle area 
	area.removeFromTop(50);
	area.removeFromBottom(10);
	rateSlider.setBounds(area.removeFromLeft(area.getWidth() / 2));
	widthSlider.setBounds(area);
}
