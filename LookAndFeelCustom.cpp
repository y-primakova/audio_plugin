/*
  ==============================================================================

    LookAndFeelCustom.cpp
    Created: 13 Feb 2024 9:52:34pm
    Author:  izmka

  ==============================================================================
*/

#include <BinaryData.h>
#include "LookAndFeelCustom.h"
//#include <include_juce_graphics.cpp>
using namespace juce;

//==============================================================================
LookAndFeelCustom::LookAndFeelCustom()
{
    //setColour(Slider::thumbColourId, Colours::yellow);
    //setColour(Slider::trackColourId, Colour(0x7f000000));

}

void LookAndFeelCustom::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, 
                                        float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    
    Image myKitty = ImageCache::getFromMemory(BinaryData::BSW_Knob_2_png, BinaryData::BSW_Knob_2_pngSize);
    const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum()); //value between 0 and 1 for current amount of rotation
    const int nFrames = myKitty.getHeight() / myKitty.getWidth(); // number of frames for vertical film strip
    const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0)); // current index from 0 --> nFrames-1

    const float radius = jmin(width / 2.0f, height / 2.0f);
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius - 1.0f;
    const float ry = centreY - radius - 1.0f;

    g.drawImage(myKitty,
        (int)rx,
        (int)ry,
        2 * (int)radius,
        2 * (int)radius,   //Dest
        0,
        frameIdx * myKitty.getWidth(),
        myKitty.getWidth(),
        myKitty.getWidth()); //Source

}

void LookAndFeelCustom::drawLinearSlider(juce::Graphics& g,
    int 	x,
    int 	y,
    int 	width,
    int 	height,
    float 	sliderPos,
    float 	minSliderPos,
    float 	maxSliderPos,
    juce::Slider::SliderStyle,
    juce::Slider& slider)
{
    Image linearSlider = ImageCache::getFromMemory(BinaryData::VerticalSlider_png, BinaryData::VerticalSlider_pngSize);
    
    float sliderRelativePos = (sliderPos - minSliderPos) / (maxSliderPos - minSliderPos);
    int sliderDrawPos = (int)(sliderRelativePos * (height - linearSlider.getHeight()));

    const double volValue = (slider.getValue() - slider.getMinimum());
    const int nFrames = linearSlider.getHeight() / linearSlider.getWidth();
    const int frameIdx = (int)ceil(volValue * ((double)nFrames - 1.0));

    g.drawImage(linearSlider,
        x, y + sliderDrawPos, width, linearSlider.getHeight(),
        0, frameIdx * linearSlider.getHeight(), linearSlider.getWidth(), linearSlider.getHeight());
}
    



/*void LookAndFeelCustom::paint(juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("LookAndFeelCustom", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void LookAndFeelCustom::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}*/
