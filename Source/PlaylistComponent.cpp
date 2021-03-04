/*
   ==============================================================================

   PlaylistComponent.cpp
Created: 20 Feb 2021 4:59:16pm
Author:  robert

==============================================================================
*/

#include <JuceHeader.h>
#include <fstream>
#include <iostream>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI &player1, DeckGUI &player2): 
    player1(player1),
    player2(player2),
    searching(false)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    loadFromFile();

    songTitle.push_back("Song 1");
    songTitle.push_back("Song 2");
    songTitle.push_back("Song 3");
    songTitle.push_back("bitch im a cow");
    songTitle.push_back("song song 2");
    songTitle.push_back("Avicii 2");


    tableComponent.getHeader().addColumn("Song Title", 1, 400);
    tableComponent.getHeader().addColumn("left Deck", 2, 50);
    tableComponent.getHeader().addColumn("right Deck", 3, 50);
    tableComponent.getHeader().addColumn("Remove", 4, 50);
    tableComponent.setModel(this);


    addAndMakeVisible(tableComponent);
    addAndMakeVisible(load);
    addAndMakeVisible(search);
    load.addListener(this);
    search.addListener(this);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
       */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
            Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    int buttonHeader = getHeight()/10;


    tableComponent.setBounds(0,buttonHeader,getWidth(),getHeight() - buttonHeader);
    load.setBounds(getWidth()/2, 0, getWidth()/2, buttonHeader);
    search.setBounds(0, 0, getWidth()/2, buttonHeader);

}


int PlaylistComponent::getNumRows()  {
    return songsFilter.size();
}

void PlaylistComponent::paintRowBackground (Graphics & g, int rowNumber, int width, int height, bool rowIsSelected) {
    if (rowIsSelected) {
        g.fillAll(Colours::orange);
    } else {
        g.fillAll(Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell (Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
    g.drawText(songsFilter[rowNumber].name, 2, 0, width - 4, height, Justification::centredLeft, true);
}

Component* PlaylistComponent::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component * existingComponentToUpdate) {
    if (columnId == 2) {
        if (existingComponentToUpdate == nullptr) {
            TextButton* btn = new TextButton{"<"};

            String id{std::to_string(rowNumber) + ",l"};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    } else if (columnId == 3) {
        if (existingComponentToUpdate == nullptr) {
            TextButton* btn = new TextButton{">"};
            std::string name = std::to_string(rowNumber) + ",r";
            std::cout << name << std::endl;

            String id{name};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    } else if (columnId == 4) {
        if (existingComponentToUpdate == nullptr) {
            TextButton* btn = new TextButton{"-"};
            std::string name = std::to_string(rowNumber) + ",-";
            std::cout << name << std::endl;

            String id{name};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}


void PlaylistComponent::buttonClicked (Button* button) {
    if (button == &load) {
        std::cout << "load a file" << std::endl;
        FileChooser chooser{"Select file..."};
        if (chooser.browseForFileToOpen()) {
            addToSongs(chooser.getResult().getFullPathName().toStdString());
        }

    } else {
        std::string name = button->getComponentID().toStdString();
        unsigned int end = name.find_first_of(',', 0);
        int id = std::stoi(name.substr(0,end));
        std::string channel = name.substr(end + 1,2);
        std::cout << "id: " << id  << " channel: " << channel << std::endl;
        // take the path, send to player to play
        if (channel == "r") {
            // play the song on the right deck
            player2.loadSong(songsFilter[id].path);
        } else if (channel == "l") {
            // play the song on the left deck
            player1.loadSong(songsFilter[id].path);
        } else if (channel == "-") {
            // remove the song
            removeFromSongs(songsFilter[id].ID);
        }
    }
}

void PlaylistComponent::textEditorTextChanged(TextEditor& editor) {
    if (editor.getText() == "") {
        searching = false;
        filterSongs();
    } else {
        searching = true;
        searchQuery = editor.getText().toStdString();
        filterSongs();
    } 
}

bool PlaylistComponent::isInterestedInFileDrag (const StringArray &files) {
    return true;
}

void PlaylistComponent::filesDropped (const StringArray &files, int x, int y) {
    std::cout << "[PlaylistComponent::filesDropped] file dropped" << std::endl;
    if (files.size() == 1) {
        // TODO: get song name from file name
        addToSongs(files[0].toStdString());
    }
}


void PlaylistComponent::addToSongs(std::string path) {
    std::string name = SongInfo::getNameFromFile(path);
    int id = songs.size();
    SongInfo song{name, File{path}, id};
    songs.push_back(song);
    saveToFile();
    filterSongs();
    // Update the list when the vector is updated
    tableComponent.updateContent();
}

void PlaylistComponent::removeFromSongs(int id) {
    for (SongInfo song : songs) {
        if (song.ID == id) {
            songs.erase(songs.begin() + id);
            filterSongs();
        }
    }
    saveToFile();
}

void PlaylistComponent::filterSongs() {
    std::cout << searching << std::endl;
    songsFilter.clear();
    if (searching) {
        std::cout << "yest" << std::endl;
        for (SongInfo song : songs) {
            if (song.name.substr(0, searchQuery.size()) == searchQuery) {
                songsFilter.push_back(song);
            }
        }
    } else {
        songsFilter = songs;
    }

    tableComponent.updateContent();
    tableComponent.repaint();
    for (SongInfo song : songsFilter) {
        std::cout << song.name << std::endl;
    }
}

void PlaylistComponent::saveToFile() {
    std::ofstream out("playlistSongs.csv");
    for (SongInfo& song : songs) {
        out << song.path.getFullPathName();
        out << "\n";
    }
    out.close();
}


void PlaylistComponent::loadFromFile() {

    std::ifstream csvFile{"playlistSongs.csv"};
    std::string line;

    if (csvFile.is_open()) {
        while(std::getline(csvFile, line)) {
            try {
                addToSongs(line);
            } catch(const std::exception& e) {
                std::cout << "PlaylistComponent::loadFromFile bad data" << std::endl;
            }
        }
    }
}
