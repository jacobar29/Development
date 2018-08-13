#include <windows.h>
#include <stdafx.h>
#include <windowsx.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#define FILE_MENU_NEW  1
#define FILE_MENU_OPEN  2
#define FILE_MENU_EXIT  3
#define TRANSPOSE_UP_BUTTON 4
#define TRANSPOSE_DOWN_BUTTON 5
#define CLEAR_BUTTON 6

// forward declerations
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void getChordsFromFile();
void AddMenus(HWND);
void AddControls(HWND);
void transpose();
void getInputText();
void printChordDiagrams();
void getModifier(int);
void clearButton();


HMENU hMenu;
HWND inputEdit;
HWND numBox;
HWND outputWindow;
int windowWidth = 500;
int windowHeight = 500;


//represents a standard octave
std::string chords[12] = { "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#" };

std::vector <std::string> inputChords; // chords taken from input section

									   // chord diagrams section stuff
std::vector <std::string> chordDiagrams; // chords read from file 
std::vector <std::string> chordsToPrint; // holds transposed chords to be printed in diagrams section

std::string tempChord;
std::string outputChords; //string printed to chord area
std::string rows[5];


int rowLength; // ensures even results spacing

std::string chord;
std::string temp;

std::string outString;
std::string baseNote;
std::string noteSuffix;

int noteIndex;
int newNoteIndex;
int modifier;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInst, LPSTR args, int ncmdshow)
{

	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
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
		// menu commands
	case WM_COMMAND:
		switch (wp)
		{
		case FILE_MENU_EXIT:
			DestroyWindow(hWnd);
			break;
		case TRANSPOSE_UP_BUTTON:
			getModifier(1);
			transpose();
			break;
		case TRANSPOSE_DOWN_BUTTON:
			getModifier(0);
			transpose();
			break;
		case CLEAR_BUTTON:
			clearButton();
			break;
		}

		break;
		// initialise menus, controls and chord arrays
	case WM_CREATE:
		getChordsFromFile();
		AddMenus(hWnd);
		AddControls(hWnd);
		break;
		//on exit
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(hWnd, msg, wp, lp);

	}
}

void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();

		AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");

	SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd)
{
	CreateWindowW(L"Static", L"Enter Chords Here: ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 0, 0, windowWidth, 50, hWnd, NULL, NULL, NULL);
	inputEdit = CreateWindowW(L"Edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 10, 60, windowWidth, 100, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Button", L"-1", WS_VISIBLE | WS_CHILD, 10, 160, 100, 50, hWnd, (HMENU)TRANSPOSE_DOWN_BUTTON, NULL, NULL);
	numBox = CreateWindowW(L"Edit", L"0", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, (int)((windowWidth / 2) - 25), 160, 50, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Button", L"+1", WS_VISIBLE | WS_CHILD, windowWidth - 110, 160, 100, 50, hWnd, (HMENU)TRANSPOSE_UP_BUTTON, NULL, NULL);
	outputWindow = CreateWindowW(L"Edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 10, 210, windowWidth, 100, hWnd, NULL, NULL, NULL);

	CreateWindowW(L"Button", L"Clear", WS_VISIBLE | WS_CHILD, windowWidth - 110, windowHeight-90, 100, 50, hWnd, (HMENU)CLEAR_BUTTON, NULL, NULL);

}

// get the modifier number(the amount to transpose chords by) 
//state = 1 increments value
//state = 0 decrements value
void getModifier(int state)
{
	//get modifier from box
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
}



void getInputText()
{
	//get text from the inputWindow, store it in vector inputChords, seperating at spaces
   	inputChords.clear();
   
	//get and convert type to std::string
	wchar_t inText[100];
	GetWindowText(inputEdit, inText, 100);
	std::wstring ws(inText);
	std::string textInput(ws.begin(), ws.end());
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
// get chords from file and store them in the array to be called when printed
void getChordsFromFile()
{
	std::ifstream chordsin;
	chordsin.open("chords.txt");
	std::string str;
  
	while (std::getline(chordsin, str))
	{
		chordDiagrams.push_back(str);
	}
	chordsin.close();

}

// transpose the chords independent of any post chord suffix, modifier must already be set using getModifier() function
void transpose()
{
	getInputText();
	outString.clear();
	chordsToPrint.clear();
	
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

void printChordDiagrams()
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
			if (chordDiagrams[j].find(chordsToPrint[i] + " ") != std::string::npos)
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
						while (rowLength != 8)
						{
							rows[currRow] += ' ';
							rowLength++;
						}
						rowLength = 0;
						if (currRow < 5)
							currRow++;
					}
				} // end for itterate through char in tempChord
			} // end if chord found loop

			j++;
		} // end while loop ( j < chordDiagrams.size())

	} // end all chords to print loop

	for (int row = 0; row < 5; row++)
		outputChords.append(rows[row] + "\r\n");
	

	
	// convert to correct type for output to outputWindow
	std::wstring stemp = std::wstring(outputChords.begin(), outputChords.end());
	LPCWSTR sw = stemp.c_str();
	SetWindowText(outputWindow, sw);

}

void clearButton()
{
	SetWindowText(outputWindow, L"");
	SetWindowText(inputEdit, L"");
	SetWindowText(numBox, L"0");
}
