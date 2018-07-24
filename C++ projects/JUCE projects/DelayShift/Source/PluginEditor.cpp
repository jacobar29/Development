/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayShiftAudioProcessorEditor::DelayShiftAudioProcessorEditor (DelayShiftAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 300);
	delayTime.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	delayTime.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(delayTime);

	decayTime.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	decayTime.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(decayTime);

	shiftSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	shiftSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(shiftSlider);


	revLevelSlider.setSliderStyle(Slider::Slider::LinearVertical);
	revLevelSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(revLevelSlider);

	delayLevelSlider.setSliderStyle(Slider::Slider::LinearVertical);
	delayLevelSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(delayLevelSlider);

	shiftLevelSlider.setSliderStyle(Slider::Slider::LinearVertical);
	shiftLevelSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(shiftLevelSlider);

	dryLevelSlider.setSliderStyle(Slider::Slider::LinearVertical);
	dryLevelSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(dryLevelSlider);

	delayVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "delayTime", delayTime);
	decayVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decayTime);
	shiftVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "shift", shiftSlider);

	revLevelVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "revLevel", revLevelSlider);
	delayLevelVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "delayLevel", delayLevelSlider);
	shiftLevelVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "shiftLevel", shiftLevelSlider);
	dryLevelVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "dryLevel", dryLevelSlider);

}

DelayShiftAudioProcessorEditor::~DelayShiftAudioProcessorEditor()
{
}

//==============================================================================
void DelayShiftAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);

	g.setColour(Colours::white);
	g.setFont(15.0f);
	juce::Rectangle<int> labels = getLocalBounds();
	g.drawText("Delay Time", labels.removeFromLeft(labels.getWidth() / 4), Justification::centred, true);
	g.drawText("Decay Time", labels.removeFromLeft(labels.getWidth() / 3), Justification::centred, true);
	g.drawText("pitch Shift", labels.removeFromLeft(labels.getWidth() / 2), Justification::centred, true);
}

void DelayShiftAudioProcessorEditor::resized()
{
	juce::Rectangle<int> area = getLocalBounds();
	delayTime.setBounds(area.removeFromLeft(area.getWidth() / 4));
	decayTime.setBounds(area.removeFromLeft(area.getWidth() / 3));
	shiftSlider.setBounds(area.removeFromLeft(area.getWidth() / 2));


	revLevelSlider.setBounds(area.removeFromLeft(area.getWidth() / 4));
	delayLevelSlider.setBounds(area.removeFromLeft(area.getWidth() / 3));
	shiftLevelSlider.setBounds(area.removeFromLeft(area.getWidth() / 2));
	dryLevelSlider.setBounds(area);
	

}
