/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 7 Feb 2021 9:33:16am
    Author:  robert

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer (AudioFormatManager& _formatManager)
    : formatManager(_formatManager), looping(false){}
DJAudioPlayer::~DJAudioPlayer(){}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate) {
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

void DJAudioPlayer::setGain(double _gain){
    if (_gain < 0 || _gain > 1.0) {
        std::cout << "[DJAudioPlayer::setGain] gain out of range" << std::endl;
    } else {
        gain = _gain;
        transportSource.setGain(gain * mixRatio); 
    }
}


void DJAudioPlayer::setMixRatio(double ratio) {
    mixRatio = ratio;
    setGain(gain);
}

void DJAudioPlayer::setSpeed(double ratio){
    if (ratio < 0 || ratio > 100.0) {
        std::cout << "[DJAudioPlayer::setSpeed] speed out of range" << std::endl;
    } else {
        resampleSource.setResamplingRatio(ratio);
    }
}
void DJAudioPlayer::setPosition(double posInSec){
    transportSource.setPosition(posInSec);
}
void DJAudioPlayer::toggleLooping() {
    if (looping) {
        looping = false;
    } else {
        looping = true;
    }

}
bool DJAudioPlayer::isLooping() {
    return looping;

}

void DJAudioPlayer::setPositionRelative(double pos) {
    if (pos < 0 || pos > 1) {
        std::cout << "[setPositionRelative] pos out of range" << std::endl;
    } else {
        double posInSec = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSec);
    }
}

double DJAudioPlayer::getPositionRelative() {
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}


void DJAudioPlayer::start(){
    transportSource.start();
}
void DJAudioPlayer::stop(){
    transportSource.stop();
}


