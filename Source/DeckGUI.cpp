/*
  ==============================================================================

    DeckGUI.cpp
    Created: 7 Feb 2021 2:21:09pm
    Author:  robert

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player) : player(_player)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    std::cout << "Deck has started" << std::endl;

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(playHead);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    playHead.addListener(this);

    volSlider.setRange(0.0,1.0);
    speedSlider.setRange(0.0,100.0);
    playHead.setRange(0.0,1.0);
}

DeckGUI::~DeckGUI()
{
}

void DeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("DeckGUI", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    double rowH = getHeight()/6;

    playButton.setBounds(0,0,getWidth(),rowH);
    stopButton.setBounds(0,rowH,getWidth(),rowH);
    loadButton.setBounds(0,rowH*5,getWidth(),rowH);
    volSlider.setBounds(0,rowH*2,getWidth(), rowH);
    speedSlider.setBounds(0,rowH*3,getWidth(), rowH);
    playHead.setBounds(0,rowH*4,getWidth(), rowH);

}


void DeckGUI::buttonClicked(Button* button) {
    if(button == &playButton) {
        std::cout << "Play button was clicked" << std::endl;
        player->start();
    }
    if(button == &stopButton) {
        std::cout << "Stop button was clicked" << std::endl;
        player->stop();
    }
    if (button == &loadButton) {
        FileChooser chooser{"Select file..."};
        if (chooser.browseForFileToOpen()) {
           player->loadURL(chooser.getResult()); 
        }
    }
}

void DeckGUI::sliderValueChanged(Slider* slider) {
    if (slider == &volSlider) {
        player->setGain(slider->getValue());
    }
    if(slider == &speedSlider) {
        player->setSpeed(slider->getValue());
    }
    if (slider == &playHead) {
        player->setPositionRelative(slider->getValue());

    }
}