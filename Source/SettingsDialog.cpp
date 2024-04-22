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

void SettingsDialog::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("SettingsDialog", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void SettingsDialog::comboBoxChanged(juce::ComboBox* comboBox) 
{
    if (comboBox == &settingsComboBox)
    {
        int selectedThemeId = settingsComboBox.getSelectedId();
    }
}
void SettingsDialog::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
