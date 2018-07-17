/*
  ==============================================================================

    Filter.cpp
    Created: 23 May 2018 10:28:03am
    Author:  J

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(DualOscSynthAudioProcessor& p, std::string name) :
	processor(p)
{
	setSize(200, 200);
	StringArray menuItems("Low Pass", "High Pass");

	filterMenu.addItemList(menuItems, 1);
	filterMenu.setJustificationType(Justification::centred);
	addAndMakeVisible(filterMenu);

	filterRes.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterRes.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	addAndMakeVisible(filterRes);

	filterCutoff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterCutoff.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	filterCutoff.setSkewFactorFromMidPoint(1000);
	addAndMakeVisible(filterCutoff);
	
	// == link attachments to their processor values == 
	filterTypeVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, std::string(name + "FilterTypeVal"), filterMenu);
	resVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, std::string(name + "FilterResVal"), filterRes);
	filterVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, std::string(name + "FilterCutoffVal"), filterCutoff);

}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
	// draws labels and handles appearance

	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // fill the background
	g.drawLine(Line<float>(0, 200, 200, 200));
	g.drawLine(Line<float>(0, 0, 0, getHeight()));
	
	// layout boxes
  	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
	juce::Rectangle<int> cutoffLabelArea(0, 55, getWidth() / 2 - 20, 20);
	juce::Rectangle<int> resLabelArea(getWidth() / 2 - 20, 55, getWidth() / 2, 20);
	
	//Create and place Labels
	g.drawText("Filter", titleArea, Justification::centredTop, false);
	g.drawText("Cutoff", cutoffLabelArea, Justification::centredTop, false);
	g.drawText("Resonance", resLabelArea, Justification::centredTop, false);
				   
}


void Filter::resized()
{
	// sets position and scaling of each GUI element

	// Layout boxes
	juce::Rectangle<int> area = getLocalBounds();
 	juce::Rectangle<int> menuArea(40, 30, 90, 20);
	juce::Rectangle<int> dialArea(10, 50, area.getWidth() - 20, area.getHeight() - 70);

	//place GUI elements within layout boxes
  	filterMenu.setBounds(menuArea);
	filterCutoff.setBounds(dialArea.removeFromLeft(dialArea.getWidth() / 2));
   	filterRes.setBounds(dialArea);


}

