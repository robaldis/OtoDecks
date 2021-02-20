/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 8 Feb 2021 1:49:23pm
    Author:  robert

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager & formatManagerToUse, 
        AudioThumbnailCache & cacheToUse) 
    : audioThump(1000, formatManagerToUse, cacheToUse), fileLoaded(false), position(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    audioThump.addChangeListener(this);

}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.setColour (Colours::orange);

    if (fileLoaded) {
        audioThump.drawChannel(g,
                getLocalBounds(), 
                0, 
                audioThump.getTotalLength(), 
                0,
                1.0f);
        g.setColour(Colours::red);
        // play head position
        g.drawRect(position*getWidth(), 0, getWidth() / 50, getHeight());


    } else {
        g.setFont (20.0f);
        g.drawText ("File not loaded... ", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
    }
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..


}


void WaveformDisplay::changeListenerCallback(ChangeBroadcaster *source) {
    repaint();
    // std::cout << "[WaveformDisplay::changeListenerCallback]" << std::endl;
}


void WaveformDisplay::loadURL(URL audioURL) {
    audioThump.clear();
    fileLoaded = audioThump.setSource(new URLInputSource(audioURL));
    if (fileLoaded) {
        std::cout << "[WaveformDisplay::loadURL] loaded" << std::endl;
    } else {
        std::cout << "[WaveformDisplay::loadURL] not loaded" << std::endl;
    }
}

void WaveformDisplay::setPositionRelative(double pos) {
    if (pos != position) {
        position = pos;      
        repaint();
    }
}
