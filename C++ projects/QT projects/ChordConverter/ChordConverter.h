#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChordConverter.h"

class ChordConverter : public QMainWindow
{
	Q_OBJECT

public:
	ChordConverter(QWidget *parent = Q_NULLPTR);
	void getInputText();
	void transpose();

	// handler functions
	public slots:
	void on_downButton_clicked();
	void on_upButton_clicked();
	void on_clearButton_clicked();


private:
	//represents a standard octave
	std::string chords[12] ={ "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#" };

	std::vector <std::string> inputChords;
	std::string chord;
	std::string temp;

	std::string outString;
	std::string baseNote;
	std::string noteSuffix;

	int noteIndex;
	int newNoteIndex;
	int modifier;

	Ui::ChordConverterClass ui;
};
