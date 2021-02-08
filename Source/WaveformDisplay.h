/*
  ==============================================================================

    WaveformDisplay.h
    Created: 8 Feb 2021 1:49:23pm
    Author:  robert

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay    : public Component, public ChangeListener
{
public:
    WaveformDisplay(AudioFormatManager & formatManagerToUse, 
            AudioThumbnailCache & cacheToUse);
    ~WaveformDisplay();

    void paint (Graphics&) override;
    void resized() override;

    void changeListenerCallback(ChangeBroadcaster *source);

    void loadURL(URL audioURL);

private:

    bool fileLoaded;
    AudioThumbnail audioThump;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
