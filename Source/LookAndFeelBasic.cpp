/*
  ==============================================================================

    LookAndFeelBasic.cpp
    Created: 21 May 2024 10:11:09pm
    Author:  izmka

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LookAndFeelBasic.h"

//==============================================================================
LookAndFeelBasic::LookAndFeelBasic()
{
    auto typeface = Typeface::createSystemTypefaceFor(BinaryData::SfOuterLimits_ttf, BinaryData::SfOuterLimits_ttfSize);
    textFont = Font(typeface);
    textFont.setHeight(14.0f);
}

void LookAndFeelBasic::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{

    Image myBasic = ImageCache::getFromMemory(BinaryData::basicSlider_png, BinaryData::basicSlider_pngSize);
    const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum()); //value between 0 and 1 for current amount of rotation
    const int nFrames = myBasic.getHeight() / myBasic.getWidth(); // number of frames for vertical film strip
    const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0)); // current index from 0 --> nFrames-1

    const float radius = jmin(width / 2.0f, height / 2.0f);
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius - 1.0f;
    const float ry = centreY - radius - 1.0f;

    g.drawImage(myBasic,
        (int)rx,
        (int)ry,
        2 * (int)radius,
        2 * (int)radius,   //Dest
        0,
        frameIdx * myBasic.getWidth(),
        myBasic.getWidth(),
        myBasic.getWidth()); //Source

    Font customFont(textFont);
    g.setFont(customFont);
    g.setColour(Colours::black);

    auto value = static_cast<int>(slider.getValue());
    juce::String text = juce::String(value);
    g.drawText(text, x, y + height, width, 20, Justification::centred);

    //slider.setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);

    slider.setColour(Slider::textBoxTextColourId, Colours::white);
}

Font LookAndFeelBasic::getLabelFont(Label& label)
{
    return textFont;
}

