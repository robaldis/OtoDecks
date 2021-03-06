/*
  ==============================================================================

    SongInfo.h
    Created: 4 Mar 2021 3:44:30pm
    Author:  robert

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <string>

class SongInfo {
    public:
        /** Initialise the song with the correct information*/
        SongInfo(std::string _name, File _path, int _id);

        // Data about the song
        std::string name;
        File path;
        int ID;


        /** returns the Name of the file given the path */
        static std::string getNameFromFile(std::string path);
        /** tokenises a string with a char seperator*/
        static std::vector<std::string> tokenise(std::string, char);
};
