/*
  ==============================================================================

    LookAndFeelBasic.h
    Created: 21 May 2024 10:11:09pm
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
class LookAndFeelBasic : public juce::LookAndFeel_V4
{
public:
	LookAndFeelBasic();

	void drawRotarySlider(juce::Graphics& g,
		int 	x,
		int 	y,
		int 	width,
		int 	height,
		float 	sliderPosProportional,
		float 	rotaryStartAngle,
		float 	rotaryEndAngle,
		juce::Slider& slider) override;
	Font getLabelFont(Label& label) override;

private:
	Font textFont;
};