/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(volSlider);

    playButton.addListener(this);
    stopButton.addListener(this);

    volSlider.addListener(this);
    
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()

    phase = 0.0;
    dphase = 0.0001;

}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!
    auto* leftChan = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto* rightChan = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
    for (auto i=0; i<bufferToFill.numSamples; ++i) {
        // double sample = rand.nextDouble() * 0.25;
        // double sample = fmod(phase, 0.2);
        double sample = sin(phase) * 0.1;


        leftChan[i] = sample;
        rightChan[i] = sample;

        phase += dphase;
    }

}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    double rowH = getHeight()/5;

    playButton.setBounds(0,0,getWidth(),rowH);
    stopButton.setBounds(0,rowH,getWidth(),rowH);
    volSlider.setBounds(0,rowH*2,getWidth(), rowH);
}

void MainComponent::buttonClicked(Button* button) {
    if(button == &playButton) {
        std::cout << "Play button was clicked" << std::endl;
    }
    if(button == &stopButton) {
        std::cout << "Stop button was clicked" << std::endl;
    }
}

void MainComponent::sliderValueChanged(Slider* slider) {

    if (slider == &volSlider) {
        std::cout << "slider moved " << slider->getValue() << std::endl;
        dphase = slider->getValue() *0.01;
    }
}
