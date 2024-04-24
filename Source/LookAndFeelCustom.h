/*
  ==============================================================================

    LookAndFeelCustom.h
    Created: 13 Feb 2024 9:52:34pm
    Author:  izmka

  ==============================================================================
*/

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
using namespace juce;

//==============================================================================
/*
*/
class LookAndFeelCustom  : public LookAndFeel_V4
{
public:
    LookAndFeelCustom();

	void drawRotarySlider(Graphics& g,
		int 	x,
		int 	y,
		int 	width,
		int 	height,
		float 	sliderPosProportional,
		float 	rotaryStartAngle,
		float 	rotaryEndAngle,
		Slider& slider) override;

	void drawLinearSlider(Graphics& g,
		int 	x,
		int 	y,
		int 	width,
		int 	height,
		float 	sliderPos,
		float 	minSliderPos,
		float 	maxSliderPos,
		Slider::SliderStyle,
		Slider& slider) override;

	void drawPopupMenuItem(Graphics& g, const Rectangle<int>& area,
		const bool isSeparator, const bool isActive,
		const bool isHighlighted, const bool isTicked,
		const bool hasSubMenu, const String& text,
		const String& shortcutKeyText,
		const Drawable* icon, const Colour* textColour) override;

	Font getLabelFont(Label& label) override;


private:
	Font textFont;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LookAndFeelCustom)
};
