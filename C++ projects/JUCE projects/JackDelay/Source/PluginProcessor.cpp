/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JackDelayAudioProcessor::JackDelayAudioProcessor()
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

}

JackDelayAudioProcessor::~JackDelayAudioProcessor()
{
}

//==============================================================================
const String JackDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JackDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JackDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JackDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JackDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JackDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JackDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JackDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String JackDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void JackDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JackDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	for (int i = 0; i < kChannels; i++)
		delay[i].prepareToPlay(sampleRate);
	
}

void JackDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JackDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void JackDelayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

      for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	  decay = *tree.getRawParameterValue("decay");
	  delayTime = *tree.getRawParameterValue("delayTime");
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
		const float* inputData = buffer.getReadPointer(channel);
		float* outputData = buffer.getWritePointer (channel);

		for (int sample = 0; sample < buffer.getNumSamples(); sample++)
		{
			outputData[sample] = delay[channel].process(inputData[sample], decay, delayTime);

		}
    }
}

//==============================================================================
bool JackDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JackDelayAudioProcessor::createEditor()
{
    return new JackDelayAudioProcessorEditor (*this);
}

//==============================================================================
void JackDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JackDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JackDelayAudioProcessor();
}
