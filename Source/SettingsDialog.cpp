/*
  ==============================================================================

    SettingsDialog.cpp
    Created: 10 Apr 2024 1:26:50am
    Author:  izmka

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SettingsDialog.h"

//==============================================================================
SettingsDialog::SettingsDialog()
{
    addAndMakeVisible(settingsComboBox);
    settingsComboBox.addItem("cat theme", 1);
    settingsComboBox.addItem("minions theme", 2);
    settingsComboBox.setSelectedId(1);

}

SettingsDialog::~SettingsDialog()
{
}

void SettingsDialog::paint (Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("SettingsDialog", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void SettingsDialog::comboBoxChanged(ComboBox* comboBox) 
{
    if (comboBox == &settingsComboBox)
    {
        int selectedThemeId = settingsComboBox.getSelectedId();
    }
}
void SettingsDialog::resized()
{

}
