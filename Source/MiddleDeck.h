/*
  ==============================================================================

    MiddleDeck.h
    Created: 1 Mar 2021 3:28:44pm
    Author:  robert

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class MiddleDeck    : public Component,
                      public Slider::Listener,
                      public Button::Listener
{
public:
    MiddleDeck(DJAudioPlayer *player1, DJAudioPlayer *player2);
    ~MiddleDeck();

    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider *slider) override;
    void buttonClicked(Button *button) override;

private:
    DJAudioPlayer *player1;
    DJAudioPlayer *player2;

    Slider mixer;
    Slider vol1;
    Slider vol2;
    
    ImageButton repeat1{"repeat1"};
    ImageButton repeat2{"repeat2"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MiddleDeck)
};
