/*
  ==============================================================================

    LookAndFeelCustom.cpp
    Created: 13 Feb 2024 9:52:34pm
    Author:  izmka

  ==============================================================================
*/

#include <BinaryData.h>
#include "LookAndFeelCustom.h"



//==============================================================================
LookAndFeelCustom::LookAndFeelCustom()
{
    setColour(PopupMenu::backgroundColourId, Colour(0xff222222));
    auto typeface = Typeface::createSystemTypefaceFor(BinaryData::SfOuterLimits_ttf, BinaryData::SfOuterLimits_ttfSize);
    textFont = Font(typeface);
    textFont.setHeight(14.0f);

}

void LookAndFeelCustom::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, 
                                        float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    
    Image sliderImage;
    if (slider.getComponentID() == "delaySlider") {
        sliderImage = ImageCache::getFromMemory(BinaryData::cat5_png, BinaryData::cat5_pngSize);
    }
    else if (slider.getComponentID() == "volumeSlider") {
        sliderImage = ImageCache::getFromMemory(BinaryData::cat5_png, BinaryData::cat5_pngSize);
    }
    else if (slider.getComponentID() == "feedbackSlider") {
        sliderImage = ImageCache::getFromMemory(BinaryData::cat5_png, BinaryData::cat5_pngSize);
    }
    else if (slider.getComponentID() == "distortionSlider") {
        sliderImage = ImageCache::getFromMemory(BinaryData::cat5_png, BinaryData::cat5_pngSize);
    }
    else {
        sliderImage = ImageCache::getFromMemory(BinaryData::cat5_png, BinaryData::cat5_pngSize);
    }
    
    const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum()); //value between 0 and 1 for current amount of rotation
    const int nFrames = sliderImage.getHeight() / sliderImage.getWidth(); // number of frames for vertical film strip
    const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0)); // current index from 0 --> nFrames-1

    const float radius = jmin(width / 2.0f, height / 2.0f);
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius - 1.0f;
    const float ry = centreY - radius - 1.0f;

    g.drawImage(sliderImage,
        (int)rx,
        (int)ry,
        2 * (int)radius,
        2 * (int)radius,   //Dest
        0,
        frameIdx * sliderImage.getWidth(),
        sliderImage.getWidth(),
        sliderImage.getWidth()); //Source

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
    Slider::SliderStyle,
    Slider& slider)
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
    
void LookAndFeelCustom::drawPopupMenuItem(Graphics& g, const Rectangle<int>& area,
    const bool isSeparator, const bool isActive,
    const bool isHighlighted, const bool isTicked,
    const bool hasSubMenu, const String& text,
    const String& shortcutKeyText,
    const Drawable* icon, const Colour* textColour)
{
    Rectangle<int> r(area);


    // Настройка цветов для фона элемента
    Colour backgroundColour = isHighlighted ? findColour(PopupMenu::highlightedBackgroundColourId)
        : findColour(PopupMenu::backgroundColourId);
    Colour textColourToUse = textColour != nullptr ? *textColour
        : findColour(PopupMenu::textColourId);

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
    int iconMarginLeft = 10;
    Rectangle<int> iconArea = r.removeFromLeft((int)(r.getHeight() * 0.7f));
    iconArea.setX(iconArea.getX() + iconMarginLeft);
    int textLeftMargin = 10;

    // Иконка, если есть
    if (icon != nullptr)
    {
        icon->drawWithin(g, iconArea.toFloat(), RectanglePlacement::centred, 2.0f);
        textLeftMargin = (int)(iconArea.getRight() - 20);
    }
    

    // Текст элемента
    g.setFont(textFont);
    r.removeFromLeft(textLeftMargin);
    g.setColour(textColourToUse);
    g.drawText(text, r, Justification::centredLeft, true);

    // Субменю стрелка, если есть
    if (hasSubMenu)
    {
        Path subMenuArrow;
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
        g.drawText(shortcutKeyText, r, Justification::centredRight, true);
    }
}

Font LookAndFeelCustom::getLabelFont(Label& label)
{
    return textFont;
}
