/*
  ==============================================================================

    Oscillator.cpp
    Created: 23 May 2018 10:28:13am
    Author:  Jack Barnes

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(SoloSynthAudioProcessor& p, string name) :
processor(p)
{	
	setSize(200, 200);
	StringArray menuItems("Sine", "Saw", "Square");

	//=================== osc1 ==================================================
   
	// ===== add GUI elements and set style =====
	oscMenu.addItemList(menuItems, 1);
	addAndMakeVisible(oscMenu);
	
   	gainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	addAndMakeVisible(gainSlider);
   
	addAndMakeVisible(freqSlider);
	freqSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	freqSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	
	// == link attachments to their processor values == 
	waveType = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, std::string(name +"WaveType"), oscMenu);
	gainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, std::string(name+ "Gain"), gainSlider);
  	freqShiftVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, std::string(name + "FreqShiftVal"), freqSlider);
	
	
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
	// draws labels and handles appearance
 
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background
	g.drawLine(Line<float>(0, 200, 200, 200));
	
	//=================== osc1 Labels ===========================================

	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
	juce::Rectangle<int> gainLabelArea(0, 55, getWidth() /2 - 20, 20);
	juce::Rectangle<int> freqLabelArea(getWidth() /2 -20, 55, getWidth() /2, 20);
	
	g.drawText("Oscillator 1", titleArea, Justification::centredTop, false);
	g.drawText("Gain", gainLabelArea, Justification::centredTop, false);
	g.drawText("Freq shift", freqLabelArea, Justification::centredTop, false);

}

void Oscillator::resized()
{
	// sets position and scaling of each GUI element

	// Layout boxes
	juce::Rectangle<int> area = getLocalBounds();
	juce::Rectangle<int> comboBoxArea(40, 30, 70, 20);
	juce::Rectangle<int> dialArea(0, 60, area.getWidth() - 20, area.getHeight() - 70);
	
	//place GUI elements within layout boxes
	oscMenu.setBounds(comboBoxArea);
	gainSlider.setBounds(dialArea.removeFromLeft(dialArea.getWidth() / 2));
	freqSlider.setBounds(dialArea);

		

}

