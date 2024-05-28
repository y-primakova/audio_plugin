#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
using namespace juce;

//==============================================================================
class HighlightButtonLookAndFeel : public LookAndFeel_V4
{
public:
    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
        bool isMouseOverButton, bool isButtonDown) override
    {
        Colour baseColour = button.findColour(TextButton::buttonColourId);

        if (isMouseOverButton || isButtonDown)
            baseColour = baseColour.withBrightness(0.6);

        g.setColour(baseColour);
        g.fillRoundedRectangle(button.getLocalBounds().toFloat(), 5.0f);

        g.setColour(Colours::black);
        g.drawRoundedRectangle(button.getLocalBounds().toFloat().reduced(1.0f), 5.0f, 1.0f);
    }
};


class NewProjectAudioProcessorEditor : public AudioProcessorEditor,
    public Slider::Listener
{
public:
    void sliderValueChanged(Slider* slider) override;
    NewProjectAudioProcessorEditor(NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    void paint(Graphics&) override;
    void resized() override;

    void NewProjectAudioProcessorEditor::off();
    void NewProjectAudioProcessorEditor::styleMenuChanged();

private:
    NewProjectAudioProcessor& audioProcessor;

    Slider sliderDelayMs;
    Slider sliderFeedback;
    Slider sliderVolume;
    Slider sliderDistortion;
    Slider sliderBlend;

    Label delayLabel;
    Label feedbackLabel;
    Label volumeLabel;
    Label distortionLabel;
    Label blendLabel;

    HighlightButtonLookAndFeel buttonLookAndFeel;
    TextButton button{ "RESET" };
    ComboBox styleMenu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NewProjectAudioProcessorEditor)
};
