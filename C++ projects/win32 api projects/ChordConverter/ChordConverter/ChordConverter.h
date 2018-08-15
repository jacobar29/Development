#pragma once

#include "resource.h"

#define TRANSPOSE_UP_BUTTON 1
#define TRANSPOSE_DOWN_BUTTON 2
#define CLEAR_BUTTON 3

#define BG_COLOR RGB(8, 93, 158)
#define BUTTON_COLOR RGB(119, 127, 151)
#define EDIT_BG_COLOR RGB(67, 136, 189)

#define hFont CreateFontW (40, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial")


LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void loadImages(HWND);
void getChordsFromFile();
void getInputText();
int getModifier(int);
void transpose(HWND, int);
void printChordDiagrams(HWND);
void clearGUI();
bool dragWindow;
//GUI elements
HWND inputWindow;
HWND numBox;
HWND outputWindow;

HBITMAP logoImage;
HBITMAP pBtnImage;
HBITMAP mBtnImage;
HBITMAP cBtnImage;

//window and image dimensions
int windowWidth = 500;
int windowHeight = 500;
int bmpWidth = 60;
int bmpHeight = 100;

std::string chords[12] = { "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#" };	//represents a standard octave
std::vector<HWND> drawnChords;	//vector of chord diagram windows drawn used to clear the gui
std::vector <std::string> inputChords; // chords taken from input section
std::vector <std::string> chordDiagrams; // chords read from file 
std::vector <std::string> chordsToPrint; // holds transposed chords prior to printing
