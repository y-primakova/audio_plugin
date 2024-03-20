/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../Builds/VisualStudio2022/LowpassHighpassFilter.h"
//==============================================================================

LowpassHighpassFilterAudioProcessor::LowpassHighpassFilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(
        BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
#else
    :
#endif
parameters(*this,
    nullptr,
    juce::Identifier("LowpassAndHighpassPlugin"),
    { std::make_unique<juce::AudioParameterFloat>(
        "cutoff_frequency",
        "Cutoff Frequency",
        juce::NormalisableRange{20.f,
                                20000.f,
                                0.1f,
                                0.2f,
                                false},
        500.f),
     std::make_unique<juce::AudioParameterBool>(
        "highpass",
        "Highpass",
        false) }) {
    cutoffFrequencyParameter =
        parameters.getRawParameterValue("cutoff_frequency");
    highpassParameter = parameters.getRawParameterValue("highpass");
}

LowpassHighpassFilterAudioProcessor::~LowpassHighpassFilterAudioProcessor()
{
}

//==============================================================================
const juce::String LowpassHighpassFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LowpassHighpassFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LowpassHighpassFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LowpassHighpassFilterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LowpassHighpassFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LowpassHighpassFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LowpassHighpassFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LowpassHighpassFilterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LowpassHighpassFilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void LowpassHighpassFilterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LowpassHighpassFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    filter.setSamplingRate(static_cast<float>(sampleRate));
}

void LowpassHighpassFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LowpassHighpassFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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


void LowpassHighpassFilterAudioProcessor::processBlock(
    juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    // JUCE default code
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
    // end of the default code

    // retrieve and set the parameter values
    const auto cutoffFrequency = cutoffFrequencyParameter->load();
    // in C++, std::atomic<T> to T conversion is equivalent to a load
    const auto highpass = *highpassParameter < 0.5f ? false : true;
    filter.setCutoffFrequency(cutoffFrequency);
    filter.setHighpass(highpass);

    // perform the filtering
    filter.processBlock(buffer, midiMessages);
}

//???????????????????

juce::AudioProcessorEditor*
LowpassHighpassFilterAudioProcessor::createEditor() {
    return new LowpassHighpassFilterAudioProcessorEditor(*this, parameters);
}

//==============================================================================
bool LowpassHighpassFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}



//==============================================================================
void LowpassHighpassFilterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void LowpassHighpassFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LowpassHighpassFilterAudioProcessor();
}
