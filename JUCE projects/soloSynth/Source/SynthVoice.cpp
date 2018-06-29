
/*
==============================================================================

SynthVoice.h
Created: 23 May 2018 10:28:23am
Author:  J

==============================================================================
*/
//todo velocity and gain? rn its one gain level regardless of velocity
// try and clarify signal chain a little,  spaghetti?
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "SynthVoice.h"

SynthVoice::SynthVoice(OscRow* oscillator1, OscRow* oscillator2, AudioProcessorValueTreeState& processorTree) 
{
	osc1 = oscillator1;
	osc2 = oscillator2;
}

bool SynthVoice::canPlaySound(SynthesiserSound* sound) 
	{
		return dynamic_cast <SynthesiserSound*>(sound) != nullptr;
	}




//=================================================================
void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) 
{
	osc1->env.trigger = 1;
	//osc2->env.trigger = 1;
	// any alteration of the midi note must happen outside of the getMidiNotInHertz function call, otherwise value errors occur,
	midiNote1 = midiNoteNumber + osc1->getFreqShiftAmount();

	frequency1 = MidiMessage::getMidiNoteInHertz(midiNote1);}

//===============================================================
	void SynthVoice::stopNote(float velocity, bool allowTailOff) 
{
	osc1->env.trigger = 0;
	allowTailOff = true;
	if (velocity = 0)
		clearCurrentNote();
}
//===============================================================
void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

//===============================================================

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{


}

//===============================================================

void SynthVoice::renderNextBlock(AudioBuffer <float> &outputBuffer, int startSample, int numSamples) 
{

	for (int sample = 0; sample < numSamples; ++sample)
	{
		for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
		{
			outputBuffer.addSample(channel, startSample, (osc1->getFilteredNote(frequency1)));
		}
		++startSample;
	}
}

//=====================================================================================