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
class SettingsDialog  : public Component
{
public:
    SettingsDialog();
    ~SettingsDialog() ;

    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged(ComboBox* comboBox);

private:
    ComboBox settingsComboBox;
};
