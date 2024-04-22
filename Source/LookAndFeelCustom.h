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


//==============================================================================
/*
*/
class LookAndFeelCustom  : public juce::LookAndFeel_V4
{
public:
    LookAndFeelCustom();

	void drawRotarySlider(juce::Graphics& g,
		int 	x,
		int 	y,
		int 	width,
		int 	height,
		float 	sliderPosProportional,
		float 	rotaryStartAngle,
		float 	rotaryEndAngle,
		juce::Slider& slider) override;

	void drawLinearSlider(juce::Graphics& g,
		int 	x,
		int 	y,
		int 	width,
		int 	height,
		float 	sliderPos,
		float 	minSliderPos,
		float 	maxSliderPos,
		juce::Slider::SliderStyle,
		juce::Slider& slider) override;

	void drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
		const bool isSeparator, const bool isActive,
		const bool isHighlighted, const bool isTicked,
		const bool hasSubMenu, const juce::String& text,
		const juce::String& shortcutKeyText,
		const juce::Drawable* icon, const juce::Colour* textColour) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LookAndFeelCustom)
};
