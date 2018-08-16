#pragma once

#include "resource.h"



LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void loadImages(HWND);
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



LPCWSTR chords[12] = { L"A",  L"A#",  L"B",  L"C",  L"C#", L"D", L"D#",  L"E", L"F",  L"F#",  L"G",  L"G#" };	//represents a standard octave
std::vector<HWND> drawnChords;	//vector of chord diagram windows drawn used to clear the gui
std::vector <std::wstring> inputChords; // chords taken from input section
std::vector <std::wstring> chordsToPrint; // holds transposed chords prior to printing
