#include <windows.h>
#include <stdafx.h>
#include <windowsx.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "ChordConverter.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInst, LPSTR args, int ncmdshow)
{

	WNDCLASSW wc = { 0 };
	wc.hbrBackground = CreateSolidBrush(BG_COLOR);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"ChordFinder";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;
	CreateWindowW(L"ChordFinder", L"Chord Converter", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, windowWidth, windowHeight, NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{

	switch (msg)
	{

		// initialise menus, controls and chord arrays
	case WM_CREATE:
		getChordsFromFile();
		loadImages(hWnd);
		AddControls(hWnd);
		SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)logoImage);

		break;
		//on exit
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	 //handle window events
	case WM_COMMAND:
		switch (wp)
		{
		case TRANSPOSE_UP_BUTTON:
			transpose(hWnd, 1);
			break;
		case TRANSPOSE_DOWN_BUTTON:
			transpose(hWnd, 0);
			break;
		case CLEAR_BUTTON:
			clearGUI();
			break;
		}
    // look and feel stuff, these are called just before each element is drawn
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wp;
		
		
		SetTextColor(hdcStatic, RGB(0, 0, 0));
		SetBkColor(hdcStatic, BG_COLOR);
		HBRUSH hbrBkgnd = CreateSolidBrush(BG_COLOR);

		return (INT_PTR)hbrBkgnd;
	}
	  	break;

	case WM_CTLCOLOREDIT:
	{
		HBRUSH hbrBkgnd;
		HDC hdcStatic = (HDC)wp;
		SetTextColor(hdcStatic, RGB(0, 0, 0));

		
		if (numBox ==(HWND) lp) 
		{
			hbrBkgnd = CreateSolidBrush(BG_COLOR);
			SetBkColor(hdcStatic, BG_COLOR);

		}
		else
		{
			hbrBkgnd = CreateSolidBrush(EDIT_BG_COLOR);
			SetBkColor(hdcStatic, EDIT_BG_COLOR);
		}
			return (INT_PTR)hbrBkgnd;

	}

	break;
	
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);

	}
}

void AddControls(HWND hWnd)
{
	CreateWindowW(L"Static", L"Enter Chords Here: ", WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTER, 0, 20, windowWidth, 30, hWnd, NULL, NULL, NULL);
	inputWindow = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER| ES_AUTOVSCROLL, 20, 60, windowWidth -55, 100, hWnd, NULL, NULL, NULL);
	outputWindow = CreateWindowW(L"Edit", L"...", WS_VISIBLE | WS_BORDER | WS_CHILD | ES_AUTOVSCROLL, 20, 230, windowWidth - 55, 50, hWnd, NULL, NULL, NULL);

	numBox = CreateWindowW(L"Edit", L"0", WS_VISIBLE | WS_CHILD |ES_CENTER| ES_NUMBER, (int)((windowWidth / 2) - 25), 170, 50, 30, hWnd, NULL, NULL, NULL);
	SendMessageW(numBox, WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessageW(hWnd, WM_CTLCOLOREDIT, NULL, (LPARAM)numBox);
	//======== Buttons =====
	HWND minusBtn = CreateWindowW(L"Button", L"-1", WS_VISIBLE | WS_CHILD | BS_BITMAP, 20, 170, 100, 50, hWnd, (HMENU)TRANSPOSE_DOWN_BUTTON, NULL, NULL);
   	SendMessage(minusBtn, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)mBtnImage);

	HWND plusBtn = CreateWindowW(L"Button", L"+1", WS_VISIBLE | WS_CHILD | BS_BITMAP, windowWidth - 135, 170, 100, 50, hWnd, (HMENU)TRANSPOSE_UP_BUTTON, NULL, NULL);
	SendMessage(plusBtn, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)pBtnImage); 
   	
	HWND clearButton = CreateWindowW(L"Button", L"Clear", WS_VISIBLE | WS_CHILD | BS_BITMAP, 20, 20, 70, 30, hWnd, (HMENU)CLEAR_BUTTON, NULL, NULL);
	SendMessage(clearButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)cBtnImage);
	

}

// get the modifier number(the amount to transpose chords by) 
//state = 1 increments value
//state = 0 decrements value
int getModifier(int state)
{
	int modifier;
	//get modifier from box, convert to std::string
	wchar_t wtemp[100];
	GetWindowText(numBox, wtemp, 256);
	std::wstring ws(wtemp);
	std::string str(ws.begin(), ws.end());
	
	// increment / decrement value, reset if exceeds bounds	
	if (state == 1)
		modifier = stoi(str) +1;
	else
		modifier = stoi(str) -1;
	
	if (modifier >= 12 || modifier <= -12)
		modifier = 0;
	
	//convert int to correct type for output
	wchar_t buffer[256];
	wsprintfW(buffer, L"%d", modifier);

	SetWindowText(numBox, buffer);
	return modifier;
}



void getInputText()
{	//get text from the inputWindow, store it in vector inputChords, seperating at spaces
   	
	inputChords.clear();
   
	//get and convert type to std::string
	wchar_t inText[100];
	GetWindowText(inputWindow, inText, 100);
	std::wstring ws(inText);
	std::string textInput(ws.begin(), ws.end());
	std::stringstream instream(textInput); 
	std::string str;
	// write all from instream to inputchords vector
	while (instream >> str)
	{
		inputChords.push_back(str);
		if (instream.peek() == ' ')		 // delimit at space
			instream.ignore();
	}
	
	//capitalise first letter of chord
	for (int i = 0; i < inputChords.size(); i++)
		inputChords[i][0] = toupper(inputChords[i][0]);

}

// get chords from file and store them in the array to be called when printed
void getChordsFromFile()
{
	std::ifstream chordsin;
	chordsin.open("chords\\chords.txt");
	std::string str;
  
	while (std::getline(chordsin, str))
	{
		chordDiagrams.push_back(str);
	}
	chordsin.close();

}

//checks if c is base note or suffix
bool is_base(char c)
{
	char bases[8] = { 'A', 'B','C','D','E','F','G','#' };
	return std::find(std::begin(bases), std::end(bases), c) != std::end(bases);
}

// transpose the chords independent of any post chord suffix, modifier must already be set using getModifier() function
void transpose(HWND hWnd, int state)
{
	int modifier = getModifier(state);
	std::string baseNote;
	std::string noteSuffix;
	getInputText();
	chordsToPrint.clear();
	int newNoteIndex = 0;

	//loop through vector
	for (int i = 0; i < inputChords.size(); i++)
	{
		std::string temp = inputChords[i];
		//clear existing string data
		baseNote.clear();
		noteSuffix.clear();

		//loop through chars in each chord, split into base and suffix
		for (int j = 0; j < temp.length(); j++)
		{
			if (is_base(temp[j]))
				baseNote += temp[j];
			else
				noteSuffix += temp[j];
		}
	
		//find position of base in array
		for (int k = 0; k < 12; k++)
		{
			if (chords[k] == baseNote)
			{
				newNoteIndex = k + modifier;
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
	printChordDiagrams(hWnd);

}

void printChordDiagrams(HWND hWnd)
{
	std::string outputString; //string printed to outputWindow
	
	//starting x and y coords for first row
	int posx = 20;	 
	int posy = 290;

	for (int i = 0; i < drawnChords.size(); i++)
		SendMessage(drawnChords[i], STM_SETIMAGE, NULL, NULL);
	
	drawnChords.clear();
	
	// loop all chords to print
	for (int i = 0; i < chordsToPrint.size(); i++)
	{
		//find chord in chorddiagrams
		int j = 0;
		while (j < chordDiagrams.size())
		{
			// if chord found
			if (chordDiagrams[j].find(chordsToPrint[i] + " ") != std::string::npos)
			{
				outputString += chordDiagrams[j];	  //add to string to be printed in outputWindow
				
				//get and convert url to LPCWSTR
				std::string bmpLocation = chordDiagrams[j + 1];
				std::wstring stemp = std::wstring(bmpLocation.begin(), bmpLocation.end());
				LPCWSTR sw = stemp.c_str();
				
				//create window and display chord image bitmap
				HWND chord = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, posx, posy, bmpWidth, bmpHeight, hWnd, NULL, NULL, NULL);
				HBITMAP	chordImage = (HBITMAP)LoadImageW(NULL, sw, IMAGE_BITMAP, bmpWidth, bmpHeight, LR_LOADFROMFILE);
				SendMessage(chord, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)chordImage);

				drawnChords.push_back(chord); //add chordwindow to drawnchords array for clearing purposes
			   
				posx += bmpWidth; //update coordinates for next chord

				//move to next row when row is full
				if (posx + bmpWidth > windowWidth)
				{
					posx = 10;
					posy += bmpHeight;
				}			
			} // end if chord found loop 
			j++;
		} 	// end while loop ( j < chordDiagrams.size())

	}	  // end all chords to print loop
	
	// convert to correct type for output to outputWindow
	std::wstring stemp = std::wstring(outputString.begin(), outputString.end());
	LPCWSTR sw = stemp.c_str();
	SetWindowText(outputWindow, sw);
	
}

//reset all gui elements
void clearGUI()
{  	
	SetWindowText(outputWindow, L"");
	SetWindowText(inputWindow, L"");
	SetWindowText(numBox, L"0");
	for (int i = 0; i < drawnChords.size(); i++)
		SendMessage(drawnChords[i], STM_SETIMAGE, NULL, NULL);
	
}

void loadImages(HWND hWnd)
{
	mBtnImage = (HBITMAP)LoadImageW(NULL, L"Images\\Minus.bmp", IMAGE_BITMAP, 100, 50, LR_LOADFROMFILE);
	pBtnImage = (HBITMAP)LoadImageW(NULL, L"Images\\Plus.bmp", IMAGE_BITMAP, 100, 50, LR_LOADFROMFILE);
  	cBtnImage = (HBITMAP)LoadImageW(NULL, L"Images\\Clear.bmp", IMAGE_BITMAP, 70, 30, LR_LOADFROMFILE);
	logoImage = (HBITMAP)LoadImageW(NULL, L"Images\\ChordConverter.ico", IMAGE_ICON, 70, 30, LR_LOADFROMFILE);


}