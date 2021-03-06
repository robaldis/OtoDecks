/*
  ==============================================================================

    DeckGUI.cpp
    Created: 7 Feb 2021 2:21:09pm
    Author:  robert

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"
#include "ColourScheme.h"



OtherLookAndFeel::OtherLookAndFeel() {
    setColour (juce::Slider::thumbColourId, juce::Colours::red);

}
void OtherLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                 const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) {
    double radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
    double centreX = (float) x + (float) width  * 0.5f;
    double centreY = (float) y + (float) height * 0.5f;
    double rx = centreX - radius;
    double ry = centreY - radius;
    double rw = radius * 2.0f;
    double angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // Background
    g.setColour(Colours::darkgrey);
    g.fillEllipse(rx, ry, rw, rw);

    // g.setColour(::ColourScheme::black);
    // g.drawEllipse(rx, ry, rw, rw, 10.0f);

    Path p;
    double pointerLength = radius;
    double pointerThickness = 5.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(AffineTransform::rotation (angle).translated (centreX,centreY));


    // pointer
    g.setColour(Colours::turquoise);
    g.fillPath(p);


    g.setColour(Colours::turquoise);
    double smallw = rw*0.3;
    g.fillEllipse(centreX -(smallw /2), centreY - (smallw/2), smallw, smallw);

}







//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, 
        AudioFormatManager & formatManagerToUse, 
        AudioThumbnailCache & cacheToUse) : player(_player),
    waveformDisplay(formatManagerToUse, cacheToUse)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    std::cout << "Deck has started" << std::endl;

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    // addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(playHead);

    addAndMakeVisible(waveformDisplay);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    playHead.addListener(this);

    volSlider.setRange(0.0,1.0);
    volSlider.setValue(1.0);
    speedSlider.setRange(0.1,5.0);
    speedSlider.setValue(1);
    speedSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0,0);
    playHead.setRange(0.0,1.0);
    playHead.setSliderStyle(Slider::Rotary);
    playHead.setLookAndFeel(&otherLookAndFeel);
    // remove the text box for play head slider
    playHead.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0,0);

    startTimer(50);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    // g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll(Colours::white);

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

    double rowH = getHeight()/8;
    double rowW = getWidth()/8;

    double padding = 10;
    waveformDisplay.setBounds(0 + padding / 2 ,0 + padding / 2,getWidth() - padding, rowH*2 - padding);
    playHead.setBounds(0,rowH*2,getWidth(), rowH*4);
    playButton.setBounds(0,rowH*7,rowW*2,rowH);
    stopButton.setBounds(rowW*6,rowH*7,rowW*2,rowH);
    speedSlider.setBounds(0,rowH*6,getWidth(), rowH);
    loadButton.setBounds(rowW*2,rowH*7,rowW*4, rowH);
/**
    volSlider.setBounds(0,rowH*2,getWidth(), rowH);
    loadButton.setBounds(0,rowH*7,getWidth(),rowH);
    */
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
            loadSong(chooser.getResult());
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

bool DeckGUI::isInterestedInFileDrag (const StringArray &files) {
    std::cout << "[isInterestedInFileDrag] File draging over window" << std::endl;
    return true;

}
void DeckGUI::filesDropped (const StringArray &files, int x, int y){
    std::cout << "[filesDropped] file dropped" << std::endl;
    if (files.size() == 1) {
        loadSong(File{files[0]});
    }

}

void DeckGUI::timerCallback() {
    double pos = player->getPositionRelative();
    if (pos > 0) {
        waveformDisplay.setPositionRelative(pos);
        // set the slider position
        playHead.setValue(pos*playHead.getMaximum());
    }
    if (pos == 1 && player->isLooping()) {
        std::cout << "timeCallback looping" << std::endl;
        player->setPosition(0);
        player->start();
    }
}

void DeckGUI::loadSong(File file) {
    player->loadURL(file); 
    waveformDisplay.loadURL(URL{file});

}
