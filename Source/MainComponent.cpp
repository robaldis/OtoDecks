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
    volSlider.setRange(0,1.0);
    speedSlider.setRange(0,10.0, 0.01);
    playHead.setRange(0,100.0, 0.01);
    
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    phase = 0.0;
    dphase = 0.0001;

    formatManager.registerBasicFormats();

    for (int i = 0; i < formatManager.getNumKnownFormats(); ++i) {
        auto audioFormat = formatManager.getKnownFormat(i);
        std::cout << audioFormat->getFormatName() << std::endl;
    }

    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);


/**
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

    */
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    transportSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // if (transportSource.getCurrentPosition() != 0) {
    //     playHead.setValue((transportSource.getCurrentPosition()/transportSource.getLengthInSeconds())*100);
    // }

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.


    double rowH = getHeight()/6;

    playButton.setBounds(0,0,getWidth(),rowH);
    stopButton.setBounds(0,rowH,getWidth(),rowH);
    loadButton.setBounds(0,rowH*5,getWidth(),rowH);
    volSlider.setBounds(0,rowH*2,getWidth(), rowH);
    speedSlider.setBounds(0,rowH*3,getWidth(), rowH);
    playHead.setBounds(0,rowH*4,getWidth(), rowH);
}

void MainComponent::buttonClicked(Button* button) {
    if(button == &playButton) {
        std::cout << "Play button was clicked" << std::endl;
        transportSource.start();
    }
    if(button == &stopButton) {
        std::cout << "Stop button was clicked" << std::endl;
        transportSource.stop();
    }
    if (button == &loadButton) {
        FileChooser chooser{"Select file..."};
        if (chooser.browseForFileToOpen()) {
           loadURL(chooser.getResult()); 
        }
    }
}

void MainComponent::sliderValueChanged(Slider* slider) {

    if (slider == &volSlider) {
        // std::cout << "slider moved " << slider->getValue() << std::endl;
        transportSource.setGain(slider->getValue());
    }
    if(slider == &speedSlider) {
        //TODO: Assertion error when slider goes to 0
        resampleSource.setResamplingRatio(slider->getValue());
    }
    if (slider == &playHead) {
        double newPos = (slider->getValue()/100) * transportSource.getLengthInSeconds();
        transportSource.setPosition(newPos);

    }
}

void MainComponent::loadURL(File file) {
    std::cout << file.getFullPathName() << std::endl;
    AudioFormatReader* reader = formatManager.createReaderFor(file);
    std::cout << reader << std::endl;
    if (reader != nullptr) { // all good
        std::cout << "New track selected" << std::endl;
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource(reader,true));
        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
        transportSource.start();
    }

}
