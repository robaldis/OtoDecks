/*
  ==============================================================================

    MiddleDeck.cpp
    Created: 1 Mar 2021 3:28:44pm
    Author:  robert

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MiddleDeck.h"

//==============================================================================
MiddleDeck::MiddleDeck()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    Image repeatImage = ImageCache::getFromMemory(BinaryData::repeatbutton_png, BinaryData::repeatbutton_pngSize);


    addAndMakeVisible(mixer);
    addAndMakeVisible(vol1);
    addAndMakeVisible(vol2);
    addAndMakeVisible(repeat1);
    addAndMakeVisible(repeat2);
    
    repeat1.setImages(true, true, true, 
            repeatImage, 0, Colour(0,0,0), 
            repeatImage, 0, Colour(255,0,0), 
            repeatImage, 0, Colour(100,0,0));
    repeat2.setImages(true, true, true, 
            repeatImage, 0, Colour(0,0,0), 
            repeatImage, 0, Colour(255,0,0), 
            repeatImage, 0, Colour(100,0,0));
 
    mixer.addListener(this);
    vol1.addListener(this);
    vol2.addListener(this);
    repeat1.addListener(this);
    repeat2.addListener(this);


    mixer.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0,0);
    vol1.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0,0);
    vol2.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0,0);

    vol1.setSliderStyle(Slider::LinearVertical);
    vol2.setSliderStyle(Slider::LinearVertical);
}

MiddleDeck::~MiddleDeck()
{
}

void MiddleDeck::paint (Graphics& g)
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
    //g.drawText ("MiddleDeck", getLocalBounds(),
    //            Justification::centred, true);   // draw some placeholder text
}

void MiddleDeck::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..


    int halfWidth = getWidth()/2;
    int smallHeight = getHeight()/5;
    int buttonPadding = getWidth()/10;

    mixer.setBounds(0, smallHeight*4, getWidth(), smallHeight);
    vol1.setBounds(0, smallHeight, halfWidth, smallHeight*3);
    vol2.setBounds(halfWidth, smallHeight, halfWidth, smallHeight * 3);
    repeat1.setBounds(0 + (buttonPadding/2), 0+ (buttonPadding/2), halfWidth- buttonPadding, smallHeight- buttonPadding);
    repeat2.setBounds(halfWidth + (buttonPadding/2), 0+ (buttonPadding/2), halfWidth- buttonPadding, smallHeight- buttonPadding);
}

void MiddleDeck::sliderValueChanged(Slider *slider) {
    if (slider == &mixer) {
        std::cout << "mixer is being pressed" << std::endl;
    }else if (slider == &vol1) {
        std::cout << "vol1 is being pressed" << std::endl;
    }else if (slider == &vol2) {
        std::cout << "vol2 is being pressed" << std::endl;
    }

}

void MiddleDeck::buttonClicked(Button *button) {
    if (button == &repeat1) {
        std::cout << "r1 is being pressed" << std::endl;

    } else if (button == &repeat2) {
        std::cout << "r2 is being pressed" << std::endl;

    }

}
