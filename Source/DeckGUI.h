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
#include "HeadLookAndFeel.h"

//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener,
                   public Slider::Listener,
                   public FileDragAndDropTarget,
                   public Timer
{
public:
    DeckGUI(DJAudioPlayer* _player, 
            AudioFormatManager & formatManagerToUse, 
            AudioThumbnailCache & cacheToUse);
    ~DeckGUI();
    
    /** Called when the button is clicked */
    void buttonClicked(Button*) override;
    /** Called when the slider value changes*/
    void sliderValueChanged(Slider*) override;

    /** Called when a file is draged over this component */
    bool isInterestedInFileDrag (const StringArray &files) override;
    /** Called when a file is dropped on this component */
    void filesDropped (const StringArray &files, int x, int y) override;

    /** Called every time the component needs to be painted */
    void paint (Graphics&) override;
    /** Called every time the window is resized */
    void resized() override;

    /** Called when when the timer */
    void timerCallback() override;
    /** Load ups a song from a path, runs everything needed to visually display
     * the song as well as actually hearing in*/
    void loadSong(File file);


private:
    HeadLookAndFeel headLookAndFeel;

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
