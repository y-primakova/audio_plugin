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
    setColour(juce::PopupMenu::backgroundColourId, juce::Colour(0xff222222));

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

    slider.setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);

    slider.setColour(Slider::textBoxTextColourId, Colours::white);


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
    
void LookAndFeelCustom::drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
    const bool isSeparator, const bool isActive,
    const bool isHighlighted, const bool isTicked,
    const bool hasSubMenu, const juce::String& text,
    const juce::String& shortcutKeyText,
    const juce::Drawable* icon, const juce::Colour* textColour)
{
    juce::Rectangle<int> r(area);

    // Настройка цветов для фона элемента
    juce::Colour backgroundColour = isHighlighted ? findColour(juce::PopupMenu::highlightedBackgroundColourId)
        : findColour(juce::PopupMenu::backgroundColourId);
    juce::Colour textColourToUse = textColour != nullptr ? *textColour
        : findColour(juce::PopupMenu::textColourId);

    // Фон элемента
    g.setColour(backgroundColour);
    g.fillRect(r);

    // Если это разделитель, рисуем линию
    if (isSeparator)
    {
        g.setColour(backgroundColour.contrasting(0.2f));
        g.fillRect(r.removeFromTop(1));
        return;
    }

    // Отступ для текста и иконки
    juce::Rectangle<int> iconArea = r.removeFromLeft((int)(r.getHeight() * 1.2f));
    int textLeftMargin = 10;

    // Иконка, если есть
    if (icon != nullptr)
    {
        icon->drawWithin(g, iconArea.toFloat(), juce::RectanglePlacement::centred, 1.0f);
        textLeftMargin = (int)(iconArea.getRight() + 5);
    }
    

    // Текст элемента
    r.removeFromLeft(textLeftMargin);
    g.setColour(textColourToUse);
    g.setFont(juce::Font(16.0f));
    g.drawText(text, r, juce::Justification::centredLeft, true);

    // Субменю стрелка, если есть
    if (hasSubMenu)
    {
        juce::Path subMenuArrow;
        subMenuArrow.addTriangle(r.getRight() - 20, r.getCentreY() - 3,
            r.getRight() - 10, r.getCentreY(),
            r.getRight() - 20, r.getCentreY() + 3);
        g.setColour(textColourToUse);
        g.fillPath(subMenuArrow);
    }

    // Краткий текст для быстрых клавиш
    if (!shortcutKeyText.isEmpty())
    {
        g.setColour(textColourToUse.withAlpha(0.6f));  // Полупрозрачный для краткости
        g.drawText(shortcutKeyText, r, juce::Justification::centredRight, true);
    }
}