/*
  ==============================================================================

    SongInfo.cpp
    Created: 4 Mar 2021 3:44:30pm
    Author:  robert

  ==============================================================================
*/

#include "SongInfo.h"

SongInfo::SongInfo(std::string _name, File _path) : name(_name), 
    path(_path)
{

}


std::string SongInfo::getNameFromFile(std::string path) {

    std::vector<std::string> splitPath;
    splitPath = tokeniser(path, '/');
    return splitPath[splitPath.size() - 1].substr(0, 4);

    return "";
}



std::vector<std::string> SongInfo::tokeniser(std::string input, char separator) {
    std::string token;
	std::vector<std::string> tokens;

	signed int start, end;

	start = input.find_first_not_of(separator, 0);

	do {
		end = input.find_first_of(separator, start);

		if (start == input.length() || start == end) {
			break;
		}
		if (end >= 0) {
			token = input.substr(start,end-start);
		}
		else {
			token = input.substr(start, input.length() - start);
		}

		tokens.push_back(token);
		start = end +1;
	}while(end>0);

	return tokens;
}
