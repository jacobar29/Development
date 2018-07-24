/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayShiftAudioProcessor::DelayShiftAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr)
#endif
{

	NormalisableRange<float> delayParam(0.1, 44100);
	tree.createAndAddParameter("delayTime", "delayTime", "delayTime", delayParam, 0.1, nullptr, nullptr);

	NormalisableRange<float> depthParam(0., 1);
	tree.createAndAddParameter("decay", "Decay", "decay", depthParam, 0.8, nullptr, nullptr);

	NormalisableRange<float> shiftParam(-5, 5, 1 );
	tree.createAndAddParameter("shift", "Shift", "shift", shiftParam, 0, nullptr, nullptr);

	NormalisableRange<float> revLevelParam(0.0, 0.5f);
	tree.createAndAddParameter("revLevel", "RevLevel", "revLevel", revLevelParam, 0.2, nullptr, nullptr);
	NormalisableRange<float> delayLevelParam(0.0f, 0.5f);
	tree.createAndAddParameter("delayLevel", "DelayLevel", "delayLevel", delayLevelParam, 0.4, nullptr, nullptr); 
	NormalisableRange<float> shiftLevelParam(0.0f, 0.5f);
	tree.createAndAddParameter("shiftLevel", "ShiftLevel", "shiftLevel", shiftLevelParam, 0.2, nullptr, nullptr); 
	NormalisableRange<float> dryLevelParam(0.0f, 1.0f);
	tree.createAndAddParameter("dryLevel", "DryLevel", "dryLevel", dryLevelParam, 1, nullptr, nullptr);



}

DelayShiftAudioProcessor::~DelayShiftAudioProcessor()
{
}

//==============================================================================
const String DelayShiftAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DelayShiftAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DelayShiftAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DelayShiftAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DelayShiftAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DelayShiftAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DelayShiftAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DelayShiftAudioProcessor::setCurrentProgram (int index)
{
}

const String DelayShiftAudioProcessor::getProgramName (int index)
{
    return {};
}

void DelayShiftAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DelayShiftAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	for (int i = 0; i < kChannels; i++)
		delay[i].prepareToPlay(sampleRate);
}

void DelayShiftAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DelayShiftAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DelayShiftAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	decay = *tree.getRawParameterValue("decay");
	delayTime = *tree.getRawParameterValue("delayTime");
	float shiftFactor = *tree.getRawParameterValue("shift");

	//levels
	float revLevel = *tree.getRawParameterValue("revLevel");
	float delayLevel = *tree.getRawParameterValue("delayLevel");
	float shiftLevel = *tree.getRawParameterValue("shiftLevel");
	float dryLevel = *tree.getRawParameterValue("dryLevel");

	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		const float* inputData = buffer.getReadPointer(channel);
		float* outputData = buffer.getWritePointer(channel);

		for (int sample = 0; sample < buffer.getNumSamples(); sample++)
		{
			outputData[sample] = delay[channel].process(inputData[sample], decay, delayTime, shiftFactor, revLevel, delayLevel, shiftLevel, dryLevel);

		}
	}
}

//==============================================================================
bool DelayShiftAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DelayShiftAudioProcessor::createEditor()
{
    return new DelayShiftAudioProcessorEditor (*this);
}

//==============================================================================
void DelayShiftAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DelayShiftAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DelayShiftAudioProcessor();
}
