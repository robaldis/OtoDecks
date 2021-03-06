/*
  ==============================================================================

    HeadLookAndFeel.cpp
    Created: 6 Mar 2021 5:37:05pm
    Author:  robert

  ==============================================================================
*/

#include "HeadLookAndFeel.h"


HeadLookAndFeel::HeadLookAndFeel() {
    setColour (juce::Slider::thumbColourId, juce::Colours::red);

}


void HeadLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                 const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) {

    double radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
    double centreX = (float) x + (float) width  * 0.5f;
    double centreY = (float) y + (float) height * 0.5f;
    double rx = centreX - radius;
    double ry = centreY - radius;
    double rw = radius * 2.0f;
    double angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // Background
    g.setColour(Colours::darkgrey);
    g.fillEllipse(rx, ry, rw, rw);

    // g.setColour(::ColourScheme::black);
    // g.drawEllipse(rx, ry, rw, rw, 10.0f);

    Path p;
    double pointerLength = radius;
    double pointerThickness = 5.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(AffineTransform::rotation (angle).translated (centreX,centreY));


    // pointer
    g.setColour(Colours::turquoise);
    g.fillPath(p);


    g.setColour(Colours::turquoise);
    double smallw = rw*0.3;
    g.fillEllipse(centreX -(smallw /2), centreY - (smallw/2), smallw, smallw);

}
