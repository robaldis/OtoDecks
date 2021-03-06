/*
  ==============================================================================

    HeadLookAndFeel.h
    Created: 6 Mar 2021 5:37:05pm
    Author:  robert

  ==============================================================================
*/

#include <JuceHeader.h>

#pragma once
class HeadLookAndFeel : public LookAndFeel_V4
{
    public: 
        HeadLookAndFeel();
        /** How to draw a rotary slider */
        void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;
};
