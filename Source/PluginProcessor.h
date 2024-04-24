#pragma once

#include <JuceHeader.h>
using namespace juce;


class NewProjectAudioProcessor : public AudioProcessor
{
public:
    NewProjectAudioProcessor();
    ~NewProjectAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(AudioBuffer<float>&, MidiBuffer&) override;


    const String getName() const override;

    AudioProcessorEditor* createEditor() override;
    
    bool hasEditor() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
    void changeProgramName(int index, const String& newName) override;

    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    double changeDelayMs;
    double changeFeedback;
    double changeVolume;
    double changeDistortion;
    double changeBlend;


private:
    void fillBuffer(AudioBuffer<float>& buffer, int channel);
    void readFromBuffer(AudioBuffer<float>& buffer, AudioBuffer<float>& delayBuffer, int channel);
    void updateBufferPositions(AudioBuffer<float>& buffer, AudioBuffer<float>& delayBuffer);

    AudioBuffer<float> delayBuffer;
    int writePosition{ 0 };

  


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NewProjectAudioProcessor)
};
