#pragma once

#include <JuceHeader.h>


class NewProjectAudioProcessor : public juce::AudioProcessor
{
public:
    NewProjectAudioProcessor();
    ~NewProjectAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;


    const juce::String getName() const override;

    juce::AudioProcessorEditor* createEditor() override;
    
    bool hasEditor() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    double changeDelayMs;
    double changeFeedback;
    double changeVolume;
    double changeDistortion;
    double changeBlend;


private:
    void fillBuffer(juce::AudioBuffer<float>& buffer, int channel);
    void readFromBuffer(juce::AudioBuffer<float>& buffer, juce::AudioBuffer<float>& delayBuffer, int channel);
    void updateBufferPositions(juce::AudioBuffer<float>& buffer, juce::AudioBuffer<float>& delayBuffer);

    juce::AudioBuffer<float> delayBuffer;
    int writePosition{ 0 };

  


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NewProjectAudioProcessor)
};
