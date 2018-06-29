/*
  ==============================================================================

    SynthSound.h
    Created: 23 May 2018 10:28:30am
    Author:  J

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound 
{

	
public:
	bool appliesToNote(int midiNoteNumber)
	{
		return true;
	}


	bool appliesToChannel(int midiChannel)
	{
		return true;
	}

};