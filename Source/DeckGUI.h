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
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener,
                   public Slider::Listener,
                   public FileDragAndDropTarget
{
public:
    DeckGUI(DJAudioPlayer* _player, 
            AudioFormatManager & formatManagerToUse, 
            AudioThumbnailCache & cacheToUse);
    ~DeckGUI();
    
    void buttonClicked(Button*);
    void sliderValueChanged(Slider*);

    bool isInterestedInFileDrag (const StringArray &files);
    void filesDropped (const StringArray &files, int x, int y);

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

    WaveformDisplay waveformDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
