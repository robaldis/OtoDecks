/*
  ==============================================================================

    MiddleDeck.h
    Created: 1 Mar 2021 3:28:44pm
    Author:  robert

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MiddleDeck    : public Component,
                      public Slider::Listener
{
public:
    MiddleDeck();
    ~MiddleDeck();

    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider *slider) override;


private:

    Slider mixer;
    Slider vol1;
    Slider vol2;

    Image normalImage{Image::ARGB, 64,64 true};

    ImageButton repeat1{"repeat1"};
    ImageButton repeat2{"repeat2"};


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MiddleDeck)
};
