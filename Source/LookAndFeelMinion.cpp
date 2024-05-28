/*
  ==============================================================================

    LookAndFeelMinion.cpp
    Created: 22 Apr 2024 4:34:14pm
    Author:  izmka

  ==============================================================================
*/

#include "LookAndFeelMinion.h"
#include <BinaryData.h>
//#include <include_juce_graphics.cpp>
using namespace juce;

//==============================================================================
LookAndFeelMinion::LookAndFeelMinion()
{
    auto typeface = Typeface::createSystemTypefaceFor(BinaryData::SfOuterLimits_ttf, BinaryData::SfOuterLimits_ttfSize);
    textFont = Font(typeface);
    textFont.setHeight(14.0f);
}

void LookAndFeelMinion::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{

    Image myMinion = ImageCache::getFromMemory(BinaryData::minionSlider_png, BinaryData::minionSlider_pngSize);
    const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum()); //value between 0 and 1 for current amount of rotation
    const int nFrames = myMinion.getHeight() / myMinion.getWidth(); // number of frames for vertical film strip
    const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0)); // current index from 0 --> nFrames-1

    const float radius = jmin(width / 2.0f, height / 2.0f);
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius - 1.0f;
    const float ry = centreY - radius - 1.0f;

    g.drawImage(myMinion,
        (int)rx,
        (int)ry,
        2 * (int)radius,
        2 * (int)radius,   //Dest
        0,
        frameIdx * myMinion.getWidth(),
        myMinion.getWidth(),
        myMinion.getWidth()); //Source

    Font customFont(textFont);
    g.setFont(customFont);
    g.setColour(Colours::white);

    auto value = static_cast<int>(slider.getValue());
    juce::String text = juce::String(value);
    g.drawText(text, x, y + height, width, 20, Justification::centred);

    slider.setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
    slider.setColour(Slider::textBoxTextColourId, Colours::white);

}

Font LookAndFeelMinion::getLabelFont(Label& label)
{
    return textFont;
}
