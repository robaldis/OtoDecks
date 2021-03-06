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

    void changeListenerCallback(ChangeBroadcaster *source) override;

    /** Load a song to generate the waveform from it */
    void loadURL(URL audioURL);
    /** set the relative position of the playhead */
    void setPositionRelative(double pos);

private:

    bool fileLoaded;
    AudioThumbnail audioThump;

    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
