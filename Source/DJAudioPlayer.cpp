/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 7 Feb 2021 9:33:16am
    Author:  robert

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(){}
DJAudioPlayer::~DJAudioPlayer(){}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate) {
    formatManager.registerBasicFormats();

    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

}

void DJAudioPlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) {
    resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources() {
    transportSource.releaseResources();
}

void DJAudioPlayer::loadURL(File file){
    std::cout << file.getFullPathName() << std::endl;
    // This is cuasing the bug stopping files from playing
    AudioFormatReader* reader = formatManager.createReaderFor(file);
    if (reader != nullptr) { // all good
        std::cout << "New track selected" << std::endl;
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource(reader,true));
        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
        transportSource.start();
    }

}

void DJAudioPlayer::setGain(double gain){
}
void DJAudioPlayer::setSpeed(double speed){
}
void DJAudioPlayer::setPosition(double posInSec){
}
double DJAudioPlayer::getLengthInSeconds(){
    return transportSource.getLengthInSeconds();
}

void DJAudioPlayer::start(){
    transportSource.start();
}
void DJAudioPlayer::stop(){
    transportSource.stop();
}


