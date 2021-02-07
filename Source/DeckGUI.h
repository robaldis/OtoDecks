/*
  ==============================================================================

    DeckGUI.h
    Created: 7 Feb 2021 2:21:09pm
    Author:  robert

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener,
                   public Slider::Listener
{
public:
    DeckGUI(DJAudioPlayer* _player);
    ~DeckGUI();
    
    void buttonClicked(Button*);
    void sliderValueChanged(Slider*);

    void paint (Graphics&) override;
    void resized() override;

private:

    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    Slider volSlider;
    Slider speedSlider;
    Slider playHead;

    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
