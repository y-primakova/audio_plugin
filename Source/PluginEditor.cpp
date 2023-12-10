#include "PluginProcessor.h"
#include "PluginEditor.h"


NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor(NewProjectAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{   
    setSize(400, 300);

    addAndMakeVisible(sliderDelayMs);
    sliderDelayMs.setRange(0.0f, 1.0f);
    sliderDelayMs.setValue(0.0f);
    sliderDelayMs.setTextBoxStyle(juce::Slider::TextBoxBelow, 0, 100, 20);
    sliderDelayMs.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderDelayMs.addListener(this);

    addAndMakeVisible(sliderFeedback);
    sliderFeedback.setRange(0.0f, 1.0f);
    sliderFeedback.setValue(0.0f);
    sliderFeedback.setTextBoxStyle(juce::Slider::TextBoxBelow, 0, 100, 20);
    sliderFeedback.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderFeedback.addListener(this);

    addAndMakeVisible(sliderVolume);
    sliderVolume.setRange(0.0, 2.0);
    sliderVolume.setValue(1.0);
    sliderVolume.setTextBoxStyle(juce::Slider::TextBoxBelow, 0, 100, 20);
    sliderVolume.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sliderVolume.addListener(this);

    addAndMakeVisible(sliderDistortion);
    sliderDistortion.setRange(0.07f, 1.0f);
    sliderDistortion.setValue(1.0f);
    sliderDistortion.setTextBoxStyle(juce::Slider::TextBoxBelow, 0, 100, 20);
    sliderDistortion.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderDistortion.addListener(this);

    addAndMakeVisible(button);
    button.onClick = [this]() { off(); };

    addAndMakeVisible(styleMenu);
    styleMenu.addItem("Delay", 1);
    styleMenu.addItem("Distortion", 2);
    styleMenu.addItem("Delay + Distortion", 3);
    styleMenu.onChange = [this] { styleMenuChanged(); };
    styleMenu.setSelectedId(1);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::aquamarine);
}

void NewProjectAudioProcessorEditor::resized()
{
    sliderDelayMs.setBounds(getLocalBounds().removeFromBottom(getWidth() / 3) / 1.4);
    sliderFeedback.setBounds(getLocalBounds().removeFromTop(getWidth() / 3) / 1.4);
    sliderVolume.setBounds(getLocalBounds().removeFromRight(getWidth() / 3) / 1.4);
    sliderDistortion.setBounds(getLocalBounds().removeFromLeft(getWidth() / 3) / 1.5);
    button.setBounds(getLocalBounds().removeFromBottom(getWidth() / 5));
    styleMenu.setBounds(getLocalBounds().removeFromTop(getWidth() / 10).removeFromRight(getWidth() / 3));
}

void NewProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    if (slider == &sliderDelayMs) {
        audioProcessor.changeDelayMs = sliderDelayMs.getValue();
    }
    if (slider == &sliderFeedback) {
        audioProcessor.changeFeedback = sliderFeedback.getValue();
    }
    if (slider == &sliderVolume) {
        audioProcessor.changeVolume = sliderVolume.getValue();
    }
    if (slider == &sliderDistortion) {
        audioProcessor.changeDistortion = sliderDistortion.getValue();
    }
}

void NewProjectAudioProcessorEditor::off() {
    audioProcessor.changeDelayMs = 0.0f;
    sliderDelayMs.setValue(0.0f);
    audioProcessor.changeFeedback = 0.0f;
    sliderFeedback.setValue(0.0f);
    audioProcessor.changeVolume = 1.0;
    sliderVolume.setValue(1.0);
    audioProcessor.changeDistortion = 1.0;
    sliderDistortion.setValue(1.0);
}

void NewProjectAudioProcessorEditor::styleMenuChanged()
{
    switch (styleMenu.getSelectedId())
    {
    case 1: addAndMakeVisible(sliderDelayMs);
            sliderDelayMs.addListener(this);
            addAndMakeVisible(sliderFeedback);
            sliderDistortion.addListener(this);
            off();
            removeChildComponent(&sliderDistortion);
            break;
    case 2: addAndMakeVisible(sliderDistortion);
            sliderDistortion.addListener(this);
            off();
            removeChildComponent(&sliderDelayMs);
            removeChildComponent(&sliderFeedback);
            break;
    case 3: addAndMakeVisible(sliderDelayMs);
            addAndMakeVisible(sliderFeedback);
            addAndMakeVisible(sliderDistortion);
            sliderDelayMs.addListener(this);
            sliderDistortion.addListener(this);
            sliderDistortion.addListener(this);
            off();
            break;
    default: break;
    }
}
