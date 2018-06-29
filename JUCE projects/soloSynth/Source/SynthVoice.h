
 /*
 ==============================================================================

 SynthVoice.h
 Created: 23 May 2018 10:28:23am
 Author:  J

 ==============================================================================
 */
 //todo velocity and gain? rn its one gain level regardless of velocity

#pragma once
#include "maximilian.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

 class SynthVoice : public SynthesiserVoice {

 public:
	 bool canPlaySound(SynthesiserSound* sound) override
	 {
		 return dynamic_cast <SynthesiserSound*>(sound) != nullptr;
	 }

	 //===============================================================
   

	 void getParams(AudioProcessorValueTreeState& tree, std::string osc1name, std::string osc2name)
	 {
		 // get the required parameters from the value tree	for each oscillator
		 // these are currently harcoded as attempts to dynamically call them using the oscName 
		 //as in the commented out section below have caused audio artifacts

	   /*
		osc1WaveType = *tree.getRawParameterValue(std::string(osc1name + "WaveType"));
		osc1Gain = *tree.getRawParameterValue(std::string(osc1name + "Gain"));
		osc1TransposeAmount = *tree.getRawParameterValue(String(osc1name + "FreqShiftVal"));
		osc1LfoState = *tree.getRawParameterValue(String(osc1name + "LfoState"));
		lfo1Depth = *tree.getRawParameterValue(String(osc1name + "LfoDepth"));
		lfo1Rate = *tree.getRawParameterValue(String(osc1name + "LfoSpeed"));

		env1.setAttack(*tree.getRawParameterValue(String(osc1name + "Attack")));
		env1.setDecay(*tree.getRawParameterValue(String(osc1name + "Decay")));
		env1.setSustain(*tree.getRawParameterValue(String(osc1name + "Sustain")));
		env1.setRelease(*tree.getRawParameterValue(String(osc1name + "Release")));
		osc1FilterChoice = *tree.getRawParameterValue(String(osc1name + "FilterTypeVal"));
		filter1Cutoff = *tree.getRawParameterValue(String(osc1name + "FilterCutoffVal"));
		filter1Resonance = *tree.getRawParameterValue(String(osc1name + "FilterResVal"));

		osc2WaveType = *tree.getRawParameterValue(String(osc2name + "WaveType"));
		osc2Gain = *tree.getRawParameterValue(String(osc2name + "Gain"));
		osc2TransposeAmount = *tree.getRawParameterValue(String(osc2name + "FreqShiftVal"));
		osc2LfoState = *tree.getRawParameterValue(String(osc2name + "LfoState"));
		lfoDepth2 = *tree.getRawParameterValue(String(osc2name + "LfoDepth"));
		lfoRate2 = *tree.getRawParameterValue(String(osc2name + "LfoSpeed"));

		env2.setAttack(*tree.getRawParameterValue(String(osc2name + "Attack")));
		env2.setDecay(*tree.getRawParameterValue(String(osc2name + "Decay")));
		env2.setSustain(*tree.getRawParameterValue(String(osc2name + "Sustain")));
		env2.setRelease(*tree.getRawParameterValue(String(osc2name + "Release")));
		osc2FilterChoice = *tree.getRawParameterValue(String(osc2name + "FilterTypeVal"));
		filter2Cutoff = *tree.getRawParameterValue(String(osc2name + "FilterCutoffVal"));
		filter2Resonance = *tree.getRawParameterValue(String(osc2name + "FilterResVal"));
	  */
		 
	  //Oscillator
		 osc1WaveType = *tree.getRawParameterValue("osc1WaveType");
		 osc2WaveType = *tree.getRawParameterValue("osc2WaveType");
		 osc1Gain = *tree.getRawParameterValue("osc1Gain");
		 osc2Gain = *tree.getRawParameterValue("osc2Gain");

		 osc1TransposeAmount = *tree.getRawParameterValue("osc1FreqShiftVal");
		 osc2TransposeAmount = *tree.getRawParameterValue("osc2FreqShiftVal");

		 //=== LFO ===
		 osc1LfoState = *tree.getRawParameterValue("osc1LfoState");
		 osc2LfoState = *tree.getRawParameterValue("osc2LfoState");

		 lfo1Depth = *tree.getRawParameterValue("osc1LfoDepth");
		 lfo1Rate = *tree.getRawParameterValue("osc1LfoSpeed");
		 lfoDepth2 = *tree.getRawParameterValue("osc2LfoDepth");
		 lfoRate2 = *tree.getRawParameterValue("osc2LfoSpeed");

		 // === Envelope ===
		 env1.setAttack(*tree.getRawParameterValue("osc1Attack"));
		 env1.setDecay(*tree.getRawParameterValue("osc1Decay"));
		 env1.setSustain(*tree.getRawParameterValue("osc1Sustain"));
		 env1.setRelease(*tree.getRawParameterValue("osc1Release"));

		 env2.setAttack(*tree.getRawParameterValue("osc2Attack"));
		 env2.setDecay(*tree.getRawParameterValue("osc2Decay"));
		 env2.setSustain(*tree.getRawParameterValue("osc2Sustain"));
		 env2.setRelease(*tree.getRawParameterValue("osc2Release"));

		 // === Filter === 
		 osc1FilterChoice = *tree.getRawParameterValue("osc1FilterTypeVal");
		 filter1Cutoff = *tree.getRawParameterValue("osc1FilterCutoffVal");
		 filter1Resonance = *tree.getRawParameterValue("osc1FilterResVal");

		 osc2FilterChoice = *tree.getRawParameterValue("osc2FilterTypeVal");
		 filter2Cutoff = *tree.getRawParameterValue("osc2FilterCutoffVal");
		 filter2Resonance = *tree.getRawParameterValue("osc2FilterResVal");		 	
	 }

	 void getModulationValues()	 
	 {
		 // produces the LFO carrier waves, an individual wave is given for each osc to allow independent values for each,
		 // calculates the amounts to be added to the amplitude, frequency and cutoff as determined 
		
		 // === LFO waves ===
		 LfoWave1 = (modWave.sinewave(lfo1Rate) + 1) / 2;
		 LfoWave2 = (modWave2.sinewave(lfoRate2) + 1) / 2;

		// amplitude modulation		
		 osc1AmpMod = osc1LfoState == 1 ? LfoWave1 : 0;
		 osc2AmpMod = osc2LfoState == 1 ? LfoWave2 : 0;

		// frequency modulation
		 osc1FreqModAmount = osc1LfoState == 2 ? LfoWave1 * (lfo1Depth * 1000) : 0;
		 osc2FreqModAmount = osc2LfoState == 2 ? LfoWave2 * (lfoDepth2 * 1000) : 0;

		 // cutoff modulation 
		 osc1CutoffModAmount = osc1LfoState == 3 ? LfoWave1 * (lfo1Depth * 1000) : 0;
		 osc2CutoffModAmount = osc2LfoState == 3 ? LfoWave2 * (lfoDepth2 * 1000) : 0;
		 
		 gain = osc1Gain *(1.0f - osc1AmpMod);
		 freq = osc1Frequency + osc1FreqModAmount;
		 gain2 = osc2Gain *(1.0f - osc2AmpMod);
		 freq2 = osc2Frequency + osc2FreqModAmount;
		 // cutoff is equal to the cutoff slider value +/- the modulation amount given by the LFO

		 osc1cutoff = osc1CutoffModAmount + filter1Cutoff;
		 osc2cutoff = osc2CutoffModAmount + filter2Cutoff;

	 }
	 
	 double getosc1Note()
	 {

		

	  switch (osc2WaveType)
		 {
		 case 0: return env1.adsr(osc1.sinewave(freq) * gain, env1.trigger);
			 break;

		 case 1: return env1.adsr(osc1.saw(freq) * gain, env1.trigger);
			 break;
		 case 2: return env1.adsr(osc1.square(freq) * gain, env1.trigger);
			 break;
		 default: return env1.adsr(osc1.sinewave(freq) * gain, env1.trigger);
			 break;
		 }
	 }
	
	 double getosc2Note()
	 {

		 switch (osc2WaveType)
		 {
		 case 0: return env2.adsr(osc2.sinewave(freq2) * gain2, env2.trigger);
			 break;
		 case 1: return env2.adsr(osc2.saw(freq2) * gain2, env2.trigger);
			 break;
		 case 2: return env2.adsr(osc2.square(freq2) * gain2, env2.trigger);
			 break;
		 default: return env2.adsr(osc2.sinewave(freq2) * gain2, env2.trigger);
			 break;
		 }
	 }

	 //---------------------------------------------------------------


	 double getFilteredNote()
	 {
		 getModulationValues();

		 // returns the sum of both oscillators notes post ADSR and post filter

	
					 
		 // calculate the filtered note value of each oscillator
		 switch (osc1FilterChoice)
		 {
		 case 0: wave1 = filter1.lores(getosc1Note(), osc1cutoff, filter1Resonance);
			 break;
		 case 1: wave1 = filter1.hires(getosc1Note(), osc1cutoff, filter1Resonance);
			 break;
		 default: wave1 = filter1.lores(getosc1Note(), osc1cutoff, filter1Resonance);
			 break;
		 }
	
		 switch (osc2FilterChoice)
		 {
		 case 0: wave2 = filter2.lores(getosc2Note(), osc2cutoff, filter2Resonance);
			 break;
		 case 1: wave2 = filter2.hires(getosc2Note(), osc2cutoff, filter2Resonance);
			 break;
		 default: wave2 = filter2.lores(getosc2Note(), osc2cutoff, filter2Resonance);
			 break;

		}
		
		 return wave1 + wave2;
	 }

	 //=================================================================

	 void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
	 {
		 env1.trigger = 1;
		 env2.trigger = 1;
		 osc1Frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber + osc1TransposeAmount);		 osc2Frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber + osc2TransposeAmount);

	 }

	 //===============================================================

	 void stopNote(float velocity, bool allowTailOff) override
	 {
		 env1.trigger = 0;
		 env2.trigger = 0;
		 allowTailOff = true;

		 if (velocity = 0)
			 clearCurrentNote();
	 }

	 //===============================================================

	 void pitchWheelMoved(int newPitchWheelValue)
	 {

	 }

	 //===============================================================

	 void controllerMoved(int controllerNumber, int newControllerValue)
	 {


	 }
						  
	 //===============================================================

	 
	 void renderNextBlock(AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override
	 {

		 for (int sample = 0; sample < numSamples; ++sample)
		 {
			 for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
			 {
				 outputBuffer.addSample(channel, startSample, getFilteredNote());
			 }
			 ++startSample;
		 }
	 }

	 //=====================================================================================

 private:
	 // oscillator
	 
	 //	these represent the waves produced by the oscillator post ADSR and post filter
	 double wave1;
	 double wave2;

	 // maximillian oscillators
	 maxiOsc osc1;
	 maxiOsc osc2;

	 // determines what waveform is produced by the maxiOsc
	 int osc1WaveType;
	 int osc2WaveType;
	
	 // gain and frequency values post modulation, equal to gain slider / note frequency + the modulation amount
	 float gain;
	 float freq;
	 float gain2;
	 float freq2;
	 // gain value given by the gain slider
	 float osc1Gain;
	 float osc2Gain;
	 
	 // amount of steps to transpose the incoming midinote for each oscillator 
	 float osc1TransposeAmount;
	 float osc2TransposeAmount;

	
	 // ====== LFO ====
	 // lfo carrier waves
	 maxiOsc modWave;
	 maxiOsc modWave2;

	 // LFO parameter slider values
	 float lfo1Depth;
	 float lfo1Rate;

	 float lfoDepth2;
	 float lfoRate2;

	 // LFO state values, determines whether LFO is bypassed, or whether amplitude, frequecny or cutoff are modulated
	 int osc1LfoState;
	 int osc2LfoState;

	 // values produced by the lfo oscillators
	 double LfoWave1;
	 double LfoWave2;

	 // modulation amounts, these are the values created by the LFO oscillators and added to the gain and frequency to acheive the LFO effect	
	 double osc1AmpMod;
	 double osc2AmpMod;

	 double osc1FreqModAmount;
	 double osc2FreqModAmount;

	 double osc1CutoffModAmount;
	 double osc2CutoffModAmount;

	 
	 // frequency for each oscillator = frequency of midinote + respective frequency modulation value provided by the LFO
	 double osc1Frequency;
	 double osc2Frequency;

	 // ======== envelope ====
	 maxiEnv env1;
	 maxiEnv env2;

	 // ===== filter =======
	 maxiFilter filter1;
	 maxiFilter filter2;

	 // determines whether the variable state filter is low pass or high pass
	 int osc1FilterChoice;
	 float filter1Cutoff;
	 float filter1Resonance;
	
	 int osc2FilterChoice;
	 float filter2Cutoff;
	 float filter2Resonance;

  	 // values for filter cutoff post modulation
	 float osc1cutoff;
	 float osc2cutoff;

 };