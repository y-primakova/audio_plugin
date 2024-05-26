#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LookAndFeelCustom.h"
#include "LookAndFeelMinion.h"
#include "LookAndFeelBasic.h"
using namespace juce;


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
    void NewProjectAudioProcessorEditor::openSettings(Button* button);
    void NewProjectAudioProcessorEditor::changeTheme(const String& themeName);
    void NewProjectAudioProcessorEditor::setEffect(const juce::String& effectName);
    void NewProjectAudioProcessorEditor::setupSliderAndLabel(Slider& slider, Label& label, const String& componentID,
        int x, int y, int width, int height, int textBoxWidth, int labelHeight);

private:
    NewProjectAudioProcessor& audioProcessor;

    LookAndFeelCustom customLookAndFeel;
    LookAndFeelMinion minionsLookAndFeel;
    LookAndFeelBasic basicLookAndFeel;

    Slider sliderDelayMs;
    Slider sliderFeedback;
    Slider sliderVolume;
    Slider sliderDistortion;
    Slider sliderBlend;

    Slider sliderReverb1;
    Slider sliderReverb2;
    Slider sliderReverb3;
    Slider sliderReverb4;
    Slider sliderReverb5;
    Slider sliderReverb6;

    Label delayLabel;
    Label feedbackLabel;
    Label volumeLabel;
    Label distortionLabel;
    Label blendLabel;

    Label reverbLabel1;
    Label reverbLabel2;
    Label reverbLabel3;
    Label reverbLabel4;
    Label reverbLabel5;
    Label reverbLabel6;

    ImageButton settingsButton;

    Image backgroundImage;

    Font customFont;

    String currentTheme = "basic";
    String currentEffect = "basic effects";

    void setupBasicEffects();
    void setupReverbEffects();

    TextButton button{ "RESET" };
    ComboBox styleMenu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NewProjectAudioProcessorEditor)
};



