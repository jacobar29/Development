/*
  ==============================================================================

    Lfo.cpp
    Created: 5 Jun 2018 4:20:01pm
    Author:  J

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Lfo.h"

//==============================================================================
Lfo::Lfo(SoloSynthAudioProcessor& p, std::string name) :
	processor(p)
{
	setSize(200, 200);

	// ===== add GUI elements and set style =====
	StringArray menuItems("Bypass", "Amp", "Freq", "Cutoff");

	lfoMenu.addItemList(menuItems, 1);
	addAndMakeVisible(lfoMenu);
	
	modDepthSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	modDepthSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(modDepthSlider);

	modRateSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	modRateSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(modRateSlider);
	
	// == link attachments to their processor values == 
	lfoState = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, std::string(name + "LfoState"), lfoMenu);
	modDepth = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, std::string(name + "LfoDepth"), modDepthSlider);
	modRate = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, std::string(name +"LfoSpeed"), modRateSlider);

	
}

Lfo::~Lfo()
{
}

void Lfo::paint (Graphics& g)
{
	// draws labels and handles appearance
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background
	g.drawLine(Line<float>(0, 200, 200, 200));
	g.drawLine(Line<float>(0, 0, 0, getHeight()));

	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
	juce::Rectangle<int> freqLabelArea(10, 70, getWidth() /2, 20);
	juce::Rectangle<int> amountLabelArea(getWidth() /2, 70, getWidth() /2, 20);

	g.drawText("Modulation", titleArea, Justification::centredTop, false);
	g.drawText("LFO Rate", freqLabelArea, Justification::centredTop, false);
	g.drawText("LFO Depth", amountLabelArea, Justification::centredTop, false);
	


}

void Lfo::resized()
{
	// sets position and scaling of each GUI element

	// Layout boxes
	juce::Rectangle<int> area = getLocalBounds();
	juce::Rectangle<int> dialArea(10,70, area.getWidth() -20, getHeight()- 60);
	juce::Rectangle<int> comboBoxArea(40, 30, 90, 20);

	lfoMenu.setBounds(comboBoxArea);
	modRateSlider.setBounds(dialArea.removeFromLeft(dialArea.getWidth() / 2));
	modDepthSlider.setBounds(dialArea);


}


