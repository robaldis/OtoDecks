/*
  ==============================================================================

    SongInfo.cpp
    Created: 4 Mar 2021 3:44:30pm
    Author:  robert

  ==============================================================================
*/

#include "SongInfo.h"

SongInfo::SongInfo(std::string _name, File _path, int _id) : name(_name), 
    path(_path), ID(_id)
{

}


std::string SongInfo::getNameFromFile(std::string path) {

    std::vector<std::string> splitPath;
    splitPath = tokenise(path, '/');
    std::string file = splitPath[splitPath.size() - 1];
    unsigned int end = file.find_first_of('.', 0);
    return file.substr(0, end);

}



std::vector<std::string> SongInfo::tokenise(std::string input, char separator) {
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


