/*
  ==============================================================================

    Envelope.cpp
    Created: 23 May 2018 10:27:54am
    Author:  J

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(DualOscSynthAudioProcessor& p, std::string name) :
	processor(p)
{
	setSize(200, 200);
	
	attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	attackSlider.setTextBoxStyle(Slider::NoTextBox, false, 0,0);
	addAndMakeVisible(attackSlider);
	aLabel.setText("A", dontSendNotification);
	aLabel.attachToComponent(&attackSlider, false);

	decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	decaySlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(decaySlider);
	dLabel.setText("D", dontSendNotification);
	dLabel.attachToComponent(&decaySlider, false);

	sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	sustainSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(sustainSlider);
	sLabel.setText("S", dontSendNotification);
	sLabel.attachToComponent(&sustainSlider, false);
	
	releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	releaseSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(releaseSlider);
	rLabel.setText("R", dontSendNotification);
	rLabel.attachToComponent(&releaseSlider, false);

	attackVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, std::string(name + "Attack"), attackSlider);
	decayVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, std::string(name + "Decay"), decaySlider);
	sustainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, std::string(name + "Sustain"), sustainSlider);
	releaseVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, std::string(name + "Release"), releaseSlider);


}

Envelope::~Envelope()
{
}

void Envelope::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background
	g.drawLine(Line<float>(0, 200, 200, 200));
	g.drawLine(Line<float>(0, 0, 0, getHeight()));

	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
	g.drawText("Envelope", titleArea, Justification::centredTop, false);
	
}

void Envelope::resized()
{  
	// sets position and scaling of each GUI element

   // Layout boxes
	juce::Rectangle<int> area = getLocalBounds();
	juce::Rectangle<int> sliderArea(20, 40, area.getWidth(), area.getHeight() -10);
	
	int sliderWidth = 25;
	int sliderHeight = area.getHeight() -40;

	//place GUI elements within layout boxes
	attackSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
	decaySlider.setBounds(sliderArea.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
	sustainSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
	releaseSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));

	
}


