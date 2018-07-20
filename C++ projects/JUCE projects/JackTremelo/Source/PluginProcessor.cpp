/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JackTremeloAudioProcessor::JackTremeloAudioProcessor()
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
	NormalisableRange<float> rateParam(1, 40);
	tree.createAndAddParameter("rate", "Rate", "rate", rateParam, 1, nullptr, nullptr);

	NormalisableRange<float> depthParam(0., 1);
	tree.createAndAddParameter("depth", "Depth", "depth", depthParam, 1, nullptr, nullptr);
}

JackTremeloAudioProcessor::~JackTremeloAudioProcessor()
{
	
}

//==============================================================================
const String JackTremeloAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JackTremeloAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JackTremeloAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JackTremeloAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JackTremeloAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JackTremeloAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JackTremeloAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JackTremeloAudioProcessor::setCurrentProgram (int index)
{
}

const String JackTremeloAudioProcessor::getProgramName (int index)
{
    return {};
}

void JackTremeloAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JackTremeloAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	for (int i = 0; i < kChannels; i++)
	{
		//initialise dsp processors for each channel at the correct sample rate
		dsp[i].prepareToPlay(sampleRate);
	}
}

void JackTremeloAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JackTremeloAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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


void JackTremeloAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{	
	//calculate number of input and output channels
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();
	
	// get required params   
	rate = *tree.getRawParameterValue("rate");
	depth = *tree.getRawParameterValue("depth");
	
	// clear buffers across all channels
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	
	for (int channel = 0; channel < buffer.getNumChannels(); channel++)
		{ 	
		//input Data
		const float* inputData = buffer.getReadPointer(channel);

		//output Data
		float* outputData = buffer.getWritePointer(channel);

		for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
			outputData[sample] = dsp[channel].process(inputData[sample], rate, depth);
		}

	}

}

//==============================================================================
bool JackTremeloAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JackTremeloAudioProcessor::createEditor()
{	
	return new JackTremeloAudioProcessorEditor(*this);
	
}


//==============================================================================
void JackTremeloAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JackTremeloAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JackTremeloAudioProcessor();
}
