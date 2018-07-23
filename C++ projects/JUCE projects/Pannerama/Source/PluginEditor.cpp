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
	addAndMakeVisible(waveMenu);
	StringArray menuItems("Sine", "Square", "Triangle");
	waveMenu.addItemList(menuItems, 1);

	
	
	rateSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	rateSlider.setTextBoxStyle(Slider::TextBoxBelow, false,50,20);
	addAndMakeVisible(rateSlider);
	

	widthSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	widthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
	addAndMakeVisible(widthSlider);

	// create slider attachments, linking sliders to their corresponding valuetree parameters
	waveType = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "waveType", waveMenu);
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
	juce::Rectangle<int> labels = getLocalBounds();
	g.drawText("Rate", labels.removeFromLeft(labels.getWidth() / 2), Justification::centred, true);
	g.drawText("depth", labels, Justification::centred, true);
}

void PanneramaAudioProcessorEditor::resized()
{
	area = getLocalBounds();
	// add GUI elements to layout by removing from rectangle area 
	waveMenu.setBounds(area.removeFromTop(50));
	area.removeFromBottom(10);
	rateSlider.setBounds(area.removeFromLeft(area.getWidth() / 2));
	widthSlider.setBounds(area);
}
