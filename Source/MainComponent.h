/*
   ==============================================================================

   This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "MiddleDeck.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public Button::Listener,
                        public Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    // AudioAppComponent overrides
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

    void buttonClicked(Button*) override;
    void sliderValueChanged(Slider*) override;

private:
    //==============================================================================
    // Your private member variables go here...
    

    Random rand;

    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100};


    DJAudioPlayer player1{formatManager};
    DJAudioPlayer player2{formatManager};

    DeckGUI deckGUI1{&player1, formatManager, thumbCache};
    DeckGUI deckGUI2{&player2, formatManager, thumbCache};
    MiddleDeck midDeck{&player1, &player2};

    MixerAudioSource mixerSource;

    PlaylistComponent playlistComponent{deckGUI1, deckGUI2};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
