/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JackDistortionAudioProcessor::JackDistortionAudioProcessor()
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
	NormalisableRange<float> thresholdParam (0.0, 2.0);
	tree.createAndAddParameter("threshold", "Threshold", "threshold", thresholdParam, 0.1, nullptr, nullptr);
	NormalisableRange<float> distTypeParam(0.0, 3.0);

	tree.createAndAddParameter("distType", "DistType", "distType", distTypeParam, 0, nullptr, nullptr);
	
	NormalisableRange<float> inputGainParam(0.0, 1.5);
	tree.createAndAddParameter("inputGain", "InputGain", "inputGain", inputGainParam, 0.8, nullptr, nullptr);

	NormalisableRange<float> volumeParam (0.0, 1.0);
	tree.createAndAddParameter("volume", "Volume", "volume", volumeParam, 0.8, nullptr, nullptr);



}

JackDistortionAudioProcessor::~JackDistortionAudioProcessor()
{
}

//==============================================================================
const String JackDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JackDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JackDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JackDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JackDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JackDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JackDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JackDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const String JackDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void JackDistortionAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JackDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void JackDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JackDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void JackDistortionAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	float threshold = 2 - *tree.getRawParameterValue("threshold");
	float volume = *tree.getRawParameterValue("volume");
	float inputGain = *tree.getRawParameterValue("inputGain");
	float negThreshold = 0 - threshold;

	
	//calculate number of input and output channels
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();
	// clear buffers across all channels
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	// assumes 2 channels
	float* channelDataL = buffer.getWritePointer(0);
	float* channelDataR = buffer.getWritePointer(1);

	// iterate through buffer
	for (int i = 0; i < buffer.getNumSamples(); ++i)
	{
		// channels summed so that both channels may be panned without losing existing stereo balance
		float channelDataC = channelDataL[i] + channelDataR[i];
		if(*tree.getRawParameterValue("distType") == 0)
			channelDataC = dist.clipSym(channelDataC * inputGain, threshold);
		else if (*tree.getRawParameterValue("distType") == 1)
			channelDataC = dist.clipAsym(channelDataC, threshold);
		else if (*tree.getRawParameterValue("distType") == 2)
			channelDataC = dist.fuzz(channelDataC, threshold);
		// write gain scaled data to left and right channels
		for (int channel = 0; channel < totalNumInputChannels; ++channel)
		{
			channelDataL[i] = channelDataC * volume;
			channelDataR[i] = channelDataC * volume;
		}
	}
}	   //ToDo  label, format

//==============================================================================
bool JackDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JackDistortionAudioProcessor::createEditor()
{
    return new JackDistortionAudioProcessorEditor (*this);
}

//==============================================================================
void JackDistortionAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JackDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JackDistortionAudioProcessor();
}
