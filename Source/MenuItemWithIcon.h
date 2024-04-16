/*
  ==============================================================================

    MenuItemWithIcon.h
    Created: 16 Apr 2024 3:04:40pm
    Author:  izmka

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MenuItemWithIcon  : public juce::Component
{
public:
    MenuItemWithIcon(const juce::String& name, std::unique_ptr<juce::Drawable> icon);
    ~MenuItemWithIcon() override;

    void paint (juce::Graphics& g) override;

private:
    juce::String itemName;
    std::unique_ptr<juce::Drawable> itemIcon;
};
