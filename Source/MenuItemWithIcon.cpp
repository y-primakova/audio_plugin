/*
  ==============================================================================

    MenuItemWithIcon.cpp
    Created: 16 Apr 2024 3:04:40pm
    Author:  izmka

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MenuItemWithIcon.h"

//==============================================================================
MenuItemWithIcon::MenuItemWithIcon(const juce::String& name, std::unique_ptr<juce::Drawable> icon)
    : itemName(name), itemIcon(std::move(icon))
{

}

MenuItemWithIcon::~MenuItemWithIcon()
{
}

void MenuItemWithIcon::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    if (itemIcon != nullptr) {
        auto iconHeight = bounds.getHeight();
        itemIcon->drawWithin(g, juce::Rectangle<float>(0, 0, iconHeight, iconHeight),
            juce::RectanglePlacement::centred | juce::RectanglePlacement::onlyReduceInSize, 1.0f);
    }
    auto textBounds = bounds.removeFromLeft(bounds.getHeight()).reduced(10, 0);
    g.drawText(itemName, textBounds, juce::Justification::centredLeft);
}

