/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
	inL.setText("Input Text Here (Sharps not flats!)", dontSendNotification);
	addAndMakeVisible(inL);
	inL.setJustificationType(Justification::centred);

	sL.setText("Transpose Value", dontSendNotification);
	sL.setJustificationType(Justification::centred);
	addAndMakeVisible(sL);

	outL.setText("Output Chords", dontSendNotification);
	addAndMakeVisible(outL);
	outL.setJustificationType(Justification::centred);

	addAndMakeVisible(input);


	transSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	transSlider.setRange(-12, 12, 1.0);
	transSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
	transSlider.addListener(this);
	addAndMakeVisible(transSlider);
		
	addAndMakeVisible(output);
	output.setJustification(Justification::horizontallyCentred);
	clear.setButtonText("Clear");
	clear.addListener(this);
	addAndMakeVisible(clear);

}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::getInputText()
{
	//get text from the inputWindow, store it in vector inputChords, seperating at spaces

	inputChords.clear();

	//std::string textInput = String::String.toStdString(input.getText());
	juce::String inText = input.getText();
	std::string textInput = inText.toStdString();
	
	std::stringstream instream(textInput); // write all from instream to inputchords vector
	while (instream >> chord)
	{
		inputChords.push_back(chord);
		if (instream.peek() == ' ')		 // delimit at space
			instream.ignore();
	}
	//capitalise first letter of chord
	for (int i = 0; i < inputChords.size(); i++)
		inputChords[i][0] = toupper(inputChords[i][0]);

}
void MainComponent::sliderValueChanged(Slider* slider)
{
	getInputText();
	outString.clear();
   
	//get modifier from slider
	modifier = slider->getValue();

	//loop through vector
	for (int i = 0; i < inputChords.size(); i++)
	{
		temp = inputChords[i];
		//clear existing string data
		baseNote.clear();
		noteSuffix.clear();

		//loop through chars in each chord, split into base and suffix
		for (int j = 0; j < temp.length(); j++)
		{
			switch (temp[j])
			{
			case 'A': baseNote += temp[j];
				break;
			case 'B': baseNote += temp[j];
				break;
			case 'C': baseNote += temp[j];
				break;
			case 'D': baseNote += temp[j];
				break;
			case 'E': baseNote += temp[j];
				break;
			case 'F': baseNote += temp[j];
				break;
			case 'G': baseNote += temp[j];
				break;
			case '#': baseNote += temp[j];
				break;
			default: noteSuffix += temp[j];
				break;
			}
		}

		//find position of base in array
		for (int k = 0; k < 12; k++)
		{
			if (chords[k] == baseNote)
			{
				noteIndex = k;
				newNoteIndex = noteIndex + modifier;
				// loop back to start or finish if end of array is exceeded
				while (newNoteIndex > 11)
					newNoteIndex -= 12;
				while (newNoteIndex < 0)
					newNoteIndex += 12;
			}
		}

		//append to output string
		outString.append(chords[newNoteIndex]);
		outString.append(noteSuffix);
		outString.append(" ");
	}

	// clear outputwindow and write output string
	output.setText(outString);

}

void MainComponent::buttonClicked(Button* button)
{
	//clear both text boxes and reset slider to 0
	input.setText("");
	output.setText("");
	transSlider.setValue(0);

}


void MainComponent::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	g.setFont(Font(16.0f));
	g.setColour(Colours::white);
}

void MainComponent::resized()
{

	juce::Rectangle<int> area = getLocalBounds();
	juce::Rectangle<int> buttonArea(area.getWidth(), 50);
	area.removeFromLeft(10);
	area.removeFromRight(10);
	area.removeFromTop(10);

	inL.setBounds(area.removeFromTop(20));
	area.removeFromTop(10);

	input.setBounds(area.removeFromTop(100));
	area.removeFromTop(10);

	sL.setBounds(area.removeFromTop(20));
	area.removeFromTop(10);

	transSlider.setBounds(area.removeFromTop(50));
	area.removeFromTop(10);

	outL.setBounds(area.removeFromTop(20));
	area.removeFromTop(10);
	output.setBounds(area.removeFromTop(100));
	area.removeFromTop(10);

	area.removeFromRight(20);
	clear.setBounds(area.removeFromRight(60).removeFromTop(40));

}
