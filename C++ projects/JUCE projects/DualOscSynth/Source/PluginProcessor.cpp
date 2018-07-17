/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

DualOscSynthAudioProcessor::DualOscSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	),
	tree(*this, nullptr), osc1(tree, "osc1"), osc2(tree, "osc2") // initialise value tree and OscValues
#endif
{
	//==========================================================================================================
	// add synth sounds and voices, five is an arbitrary value, could easily be less,
	//more voices would probably be too strenuous and cause some audio artifacts

	mySynth.clearVoices();

	for (int i = 0; i < 6; i++)
	{
		mySynth.addVoice(new SynthVoice());
	}

	mySynth.clearSounds();
	mySynth.addSound(new SynthSound());

}

DualOscSynthAudioProcessor::~DualOscSynthAudioProcessor()
{
}

//==============================================================================
const String DualOscSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DualOscSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DualOscSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DualOscSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DualOscSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DualOscSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DualOscSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DualOscSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String DualOscSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void DualOscSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DualOscSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	// sample rate is taken from the soundcard, this ensures that any change of sample rate will not cause any issues
	ignoreUnused(samplesPerBlock);
	lastSampleRate = sampleRate;
	mySynth.setCurrentPlaybackSampleRate(sampleRate);
}

void DualOscSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DualOscSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void DualOscSynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();


	// pass values from processor value tree to each synthesiser voice
	for (int i = 0; i < mySynth.getNumVoices(); i++)
	{

		if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
		{
			myVoice->getParams(tree, "osc1", "osc2");

		}

	}

	// clear all channels of the buffer to ensure there are no left over garbage values
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

}

//==============================================================================
bool DualOscSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DualOscSynthAudioProcessor::createEditor()
{
    return new DualOscSynthAudioProcessorEditor (*this);
}

//==============================================================================
void DualOscSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DualOscSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DualOscSynthAudioProcessor();
}
