/*
   ==============================================================================

   This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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

    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    Slider volSlider;
    Slider speedSlider;
    Slider playHead;
    

    Random rand;
    double phase;
    double dphase;

    // Audio reading classes
    // Allows to open many types of file formats with one class.
    AudioFormatManager formatManager;
    
    std::unique_ptr<AudioFormatReaderSource> readerSource;

    // What controls the song
    AudioTransportSource transportSource;
    // What controls the speed of the song
    ResamplingAudioSource resampleSource{&transportSource,false,2};

    void loadURL(File file);


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
