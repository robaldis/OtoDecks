/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 7 Feb 2021 9:33:16am
    Author:  robert

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DJAudioPlayer : public AudioAppComponent {
    public:
        DJAudioPlayer(AudioFormatManager& _formatManager);
        ~DJAudioPlayer();

        //==============================================================================
        // AudioAppComponent overrides
        void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;

        //==============================================================================
        void loadURL(File file);
        void setGain(double gain);
        void setSpeed(double speed);
        void setPosition(double posInSec);
        void setPositionRelative(double pos);
        double getLengthInSeconds();

        //** Get the relative to play head */
        double getPositionRelative();

        void start();
        void stop();

    private:

        // Audio reading classes
        // Allows to open many types of file formats with one class.
        AudioFormatManager& formatManager;

        std::unique_ptr<AudioFormatReaderSource> readerSource;

        // What controls the song
        AudioTransportSource transportSource;
        // What controls the speed of the song
        ResamplingAudioSource resampleSource{&transportSource,false,2};
};
