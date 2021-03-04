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
        SongInfo(std::string _name, File _path);
        std::string name;
        File path;
        int ID;
        static std::string getNameFromFile(std::string path);
        static std::vector<std::string> tokeniser(std::string, char);
};
