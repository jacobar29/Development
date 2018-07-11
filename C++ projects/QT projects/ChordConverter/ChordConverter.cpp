/*============================
 
 a simple qt application for transposing chords
 chords are extracted from the inputWindow and stored in a vector, which is then compared to an array containing the scale. 
 in the future this could be modified so that chords can be transposed along a given scale. 
 as an octave is only 12 notes long, transposing more than + or - 11 will set the lcd display back to 0
 
 there is currently no attempt to catch incorrect values entered in the inputwindow, this is so that a full range of suspended chords can be dealt with,
 as well as any personal notations you may have.
							    

  */
#include "ChordConverter.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

ChordConverter::ChordConverter(QWidget *parent)
	: QMainWindow(parent)
{
 	//initialise UI
	ui.setupUi(this);			  
}


void ChordConverter::on_upButton_clicked()
{
	//increment displayed lcdNumber and trigger transposition
	int x = ui.lcdDisplay->intValue() + 1;
	if (x > 11 || x < -11)
		x = 0;
	ui.lcdDisplay->display(x);
	transpose();
	
}

void ChordConverter::on_downButton_clicked()
{	//decrement displayed lcdNumber and trigger transposition
	int num = ui.lcdDisplay->intValue() -1;
	if (num > 11 || num < -11)
		num = 0;
	ui.lcdDisplay->display(num);
	transpose();
}

void ChordConverter::getInputText()
{
	//get text from the inputWindow, store it in vector inputChords, seperating at spaces
	
	inputChords.clear();
	
	std::string textInput = ui.inputWindow->toPlainText().toStdString();
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

void ChordConverter::transpose()
{
	getInputText();
	outString.clear();
	
	
	//get modifier from lcdDisplay
	modifier = ui.lcdDisplay->intValue();
   	
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
	ui.outputWindow->clear();
	ui.outputWindow->setText(QString::fromStdString(outString));

}
void ChordConverter::on_clearButton_clicked()
{
	//clear both text boxes and reset lcd to 0
	ui.inputWindow->setText("");
	ui.outputWindow->setText("");
	ui.lcdDisplay->display(0);
}