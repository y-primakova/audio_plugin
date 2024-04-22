#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LookAndFeelCustom.h"

//==============================================================================
/*class HighlightButtonLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
        bool isMouseOverButton, bool isButtonDown) override
    {
        juce::Colour baseColour = button.findColour(juce::TextButton::buttonColourId);

        if (isMouseOverButton || isButtonDown)
            baseColour = baseColour.withBrightness(0.6);

        g.setColour(baseColour);
        g.fillRoundedRectangle(button.getLocalBounds().toFloat(), 5.0f);

        g.setColour(juce::Colours::black);
        g.drawRoundedRectangle(button.getLocalBounds().toFloat().reduced(1.0f), 5.0f, 1.0f);
    }
};*/


class NewProjectAudioProcessorEditor : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    void sliderValueChanged(juce::Slider* slider) override;
    NewProjectAudioProcessorEditor(NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void NewProjectAudioProcessorEditor::off();
    void NewProjectAudioProcessorEditor::styleMenuChanged();
    void NewProjectAudioProcessorEditor::openSettings(juce::Button* button);

private:
    NewProjectAudioProcessor& audioProcessor;

    LookAndFeelCustom customLookAndFeel;

    juce::Slider sliderDelayMs;
    juce::Slider sliderFeedback;
    juce::Slider sliderVolume;
    juce::Slider sliderDistortion;
    juce::Slider sliderBlend;

    juce::Label delayLabel;
    juce::Label feedbackLabel;
    juce::Label volumeLabel;
    juce::Label distortionLabel;
    juce::Label blendLabel;

    juce::ImageButton settingsButton;

    juce::Image backgroundImage;

    juce::Font customFont;

    //HighlightButtonLookAndFeel buttonLookAndFeel;
    juce::TextButton button{ "RESET" };
    juce::ComboBox styleMenu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NewProjectAudioProcessorEditor)
};



