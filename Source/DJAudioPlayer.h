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
        /** Loads song from file into transport source */
        void loadURL(File file);
        /** Sets the gain of the song */
        void setGain(double gain);
        /** Sets the mix ratio */
        void setMixRatio(double ratio);
        /** sets the speed of the song*/
        void setSpeed(double speed);
        /** Toggles if the song should loop */
        void toggleLooping();
        /** Check if the song is looping */
        bool isLooping();
        /** Sets the position of what part of the song we are in 
         * This is position in seconds */
        void setPosition(double posInSec);
        /** Sets the position based on a percentage full, 0-1 */
        void setPositionRelative(double pos);
        /** Get the length of the song in seconds */
        double getLengthInSeconds();

        //** Get the relative to play head */
        double getPositionRelative();

        /** Starts the song */
        void start();
        /** Stops the song */
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

        double mixRatio;
        double gain;
        bool looping;
};
