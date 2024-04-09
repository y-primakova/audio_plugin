/*
  ==============================================================================

    SettingsDialog.h
    Created: 10 Apr 2024 1:26:50am
    Author:  izmka

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SettingsDialog  : public juce::Component
{
public:
    SettingsDialog();
    ~SettingsDialog() ;

    void paint (juce::Graphics&) override;
    void resized() override;
    void comboBoxChanged(juce::ComboBox* comboBox);

private:
    juce::ComboBox settingsComboBox;
};
