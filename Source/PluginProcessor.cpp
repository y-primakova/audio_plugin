#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <corecrt_math_defines.h>
#include "delay.cpp"
#include "distortion.cpp"
#include "volume.cpp"
#include "reverb.cpp"
#include "highpass.cpp"

using namespace std;
using namespace juce;

NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

const String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram(int index)
{
}

const String NewProjectAudioProcessor::getProgramName(int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName(int index, const String& newName)
{
}

void NewProjectAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    auto delayBufferSize = sampleRate * 2.0;
    delayBuffer.setSize(getTotalNumOutputChannels(), (int)delayBufferSize);
    reverbBuffer.setSize(getTotalNumOutputChannels(), sampleRate);
    reverbBuffer.clear();
}

void NewProjectAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void NewProjectAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    int bufferSize = buffer.getNumSamples();
    int delayBufferSize = delayBuffer.getNumSamples();
    int reverbBufferSize = reverbBuffer.getNumSamples();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; i++) {
        buffer.clear(i, 0, bufferSize);
    }

    for (int channel = 0; channel < totalNumInputChannels; channel++) {
        float* start = buffer.getWritePointer(channel);
        vector<float> myBuffer(start, start + bufferSize);
        start = delayBuffer.getWritePointer(channel);
        vector<float> myDelayBuffer(start, start + delayBufferSize);
        delay(myBuffer, myDelayBuffer, changeDelayMs, changeFeedback, getSampleRate(), writePosition);
        buffer.copyFrom(channel, 0, &myBuffer[0], bufferSize);
        delayBuffer.copyFrom(channel, 0, &myDelayBuffer[0], delayBufferSize);
    }

    writePosition = update(bufferSize, delayBufferSize, writePosition);

    for (int channel = 0; channel < totalNumInputChannels; channel++) {
        float* start = buffer.getWritePointer(channel);
        vector<float> audioBuffer(start, start + bufferSize);
        start = reverbBuffer.getWritePointer(channel);
        vector<float> reverbData(start, start + reverbBufferSize);

        distortion(audioBuffer, changeDistortion, changeBlend);
        volume(audioBuffer, changeVolume);
        process(audioBuffer, writePositionReverb, reverbData, feedback, delayTime, mix, getSampleRate());
        processHp(audioBuffer, getSampleRate(), hpcutoffFrequency, prevInput, prevOutput);

        buffer.copyFrom(channel, 0, &audioBuffer[0], bufferSize);
        reverbBuffer.copyFrom(channel, 0, &reverbData[0], reverbBufferSize);
    }
}

bool NewProjectAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor(*this);
}

void NewProjectAudioProcessor::getStateInformation(MemoryBlock& destData)
{
}

void NewProjectAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
