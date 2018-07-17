/*
==============================================================================

OscGui.cpp
Created: 19 Jun 2018 5:12:11pm
Author:  J

==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
#include "OscGui.h"


//==============================================================================
OscGui::OscGui(DualOscSynthAudioProcessor& p, std::string name) : processor(p),oscGui(p, name),lfoGui(p, name),envGui(p, name),
filterGui(p, name)
{
	setSize(750, 200);
	// gui elements 
	addAndMakeVisible(oscGui);
	addAndMakeVisible(lfoGui);
	addAndMakeVisible(envGui);
	addAndMakeVisible(filterGui);

}

OscGui::~OscGui()
{
}

void OscGui::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background
}

void OscGui::resized()
{
	const int componentWidth = 200;
	juce::Rectangle<int> area = getLocalBounds();
	oscGui.setBounds(area.removeFromLeft(componentWidth));
	lfoGui.setBounds(area.removeFromLeft(componentWidth));
	envGui.setBounds(area.removeFromLeft(componentWidth - 50));
	filterGui.setBounds(area.removeFromLeft(componentWidth));

}
