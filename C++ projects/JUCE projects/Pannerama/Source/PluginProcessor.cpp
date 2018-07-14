/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PanneramaAudioProcessor::PanneramaAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	), tree(*this, nullptr), osc()
#endif
{

	NormalisableRange<float> rateParam(1.0f, 1000.0f, 1.0f);
	tree.createAndAddParameter("panRate", "PanRate", "panRate", rateParam, 50, nullptr, nullptr);

	NormalisableRange<float> widthParam(0.0f, 1.0f, 0.1f);
	tree.createAndAddParameter("panWidth", "PanWidth", "panwidth", widthParam, 0.5, nullptr, nullptr);


}

PanneramaAudioProcessor::~PanneramaAudioProcessor()
{
}

//==============================================================================
const String PanneramaAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PanneramaAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PanneramaAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PanneramaAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PanneramaAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PanneramaAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PanneramaAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PanneramaAudioProcessor::setCurrentProgram (int index)
{
}

const String PanneramaAudioProcessor::getProgramName (int index)
{
    return {};
}

void PanneramaAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PanneramaAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	// initialize values
	osc.setSampleRate(sampleRate);
}

void PanneramaAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PanneramaAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void PanneramaAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	//generate sin wave, increment phase
	frequency = *tree.getRawParameterValue("panRate");
	wave = osc.sawWave(frequency);

	
	lGainVal = 1 - wave;
	rGainVal = 1 + wave;

	// addition of a portion of the dry signal to each channel creates the illusion of reduced pan width
	// max width is a dry gain of 0, min is 1, slider value is inverted so that max slider value = max width
	dryGain = 1 - *tree.getRawParameterValue("panWidth") + 0.2;

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

		// write gain scaled data to left and right channels
		for (int channel = 0; channel < totalNumInputChannels; ++channel)
		{
			channelDataL[i] = lGainVal*channelDataC + dryGain*channelDataC;
			channelDataR[i] = rGainVal*channelDataC + dryGain*channelDataC;
		}
	}

}

//==============================================================================
bool PanneramaAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PanneramaAudioProcessor::createEditor()
{
    return new PanneramaAudioProcessorEditor (*this);
}

//==============================================================================
void PanneramaAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PanneramaAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PanneramaAudioProcessor();
}
