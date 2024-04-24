/*
  ==============================================================================

    LookAndFeelMinion.h
    Created: 22 Apr 2024 4:34:14pm
    Author:  izmka

  ==============================================================================
*/

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>


//==============================================================================
/*
*/
class LookAndFeelMinion : public juce::LookAndFeel_V4
{
public:
	LookAndFeelMinion();

	void drawRotarySlider(juce::Graphics& g,
		int 	x,
		int 	y,
		int 	width,
		int 	height,
		float 	sliderPosProportional,
		float 	rotaryStartAngle,
		float 	rotaryEndAngle,
		juce::Slider& slider) override;


private:
		juce::Font textFont;
};