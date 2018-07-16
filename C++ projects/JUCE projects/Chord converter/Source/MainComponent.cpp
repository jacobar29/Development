/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include <iostream>
//==============================================================================
MainComponent::MainComponent()
{
	getChordsFromFile();
    setSize (800, 400);
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

	clear.setButtonText("Clear");
	clear.addListener(this);
	addAndMakeVisible(clear);

}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::getChordsFromFile()
{
	std::ifstream chordsin;
	chordsin.open("C:\\Users\\J\\Development\\C++ projects\\JUCE projects\\Chord converter\\Source\\chords.txt");
	std::string str;
	

	while (std::getline(chordsin, str))
	{
		chordDiagrams.push_back(str);
	}
	chordsin.close();

 }

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

void MainComponent::printChordDiagrams()
{
   //clear gui and rows array
	outputChords.clear();
	for (int i = 0; i < 6; i++)
		rows[i].clear();
		
	// loop all chords to print
	for (int i = 0; i < chordsToPrint.size(); i++)
	{
		//find chord in chorddiagrams
		int j = 0;	
		while (j < chordDiagrams.size())
		{	
			rowLength = chordsToPrint[i].length();
			
			// if chord found
			if (chordDiagrams[j].find(chordsToPrint[i]+ " ") != std::string::npos)
			{
				// extract chord diagram to string
				tempChord = chordDiagrams[j];
			  	int currRow = 0;
				//loop through characters of chord
				for (int pos = 0; pos < tempChord.length(); pos++)
				{
					// if not whitespace or the | deonting end of chord in the text file
					if (tempChord[pos] != ' ' && tempChord[pos] != '|' && tempChord[pos] != '\n')
					{
						rows[currRow] += tempChord[pos];
						rowLength++;
					}
				  	else
					{
						// ensure even spacing of chords by adding whitespace until row is the correct length
						while(rowLength != 8)
						{
							rows[currRow] += ' ';
							rowLength++;
						}
						rowLength = 0;
						if(currRow < 5)
							currRow++;
					   }
				} // end for itterate through char in tempChord
			} // end if chord found loop

			j++;
		} // end while loop ( j < chordDiagrams.size())
			
	} // end all chords to print loop
	
	for (int row = 0; row < 5; row++)
		outputChords.append(rows[row] + "\n");
	output.setText(outputChords);
}


void MainComponent::sliderValueChanged(Slider* slider)
{
	getInputText();
	outString.clear();
	chordsToPrint.clear();

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

		//append to output string and chordsToPrint
		chordsToPrint.push_back((chords[newNoteIndex] + noteSuffix));

	}

	// clear outputwindow and write  string
	printChordDiagrams();

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
	juce::Rectangle<int> buttonArea(area.getWidth() - 200, 50);
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
