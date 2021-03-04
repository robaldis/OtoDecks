/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 20 Feb 2021 4:59:16pm
    Author:  robert

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI &player1, DeckGUI &player2): 
    player1(player1),
    player2(player2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    songTitle.push_back("Song 1");
    songTitle.push_back("Song 2");
    songTitle.push_back("Song 3");
    songTitle.push_back("bitch im a cow");
    songTitle.push_back("song song 2");
    songTitle.push_back("Avicii 2");


    tableComponent.getHeader().addColumn("Song Title", 1, 400);
    tableComponent.getHeader().addColumn("", 2, 200);
    tableComponent.setModel(this);


    addAndMakeVisible(tableComponent);
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

    tableComponent.setBounds(0,0,getWidth(),getHeight());

}


int PlaylistComponent::getNumRows()  {
    return songs.size();
}
void PlaylistComponent::paintRowBackground (Graphics & g, int rowNumber, int width, int height, bool rowIsSelected) {
    if (rowIsSelected) {
        g.fillAll(Colours::orange);
    } else {
        g.fillAll(Colours::darkgrey);
    }


}
void PlaylistComponent::paintCell (Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
    g.drawText(songs[rowNumber].name, 2, 0, width - 4, height, Justification::centredLeft, true);
}


/** allows you to put custome components int a cell */
Component* PlaylistComponent::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component * existingComponentToUpdate) {
    if (columnId == 2) {
        if (existingComponentToUpdate == nullptr) {
            TextButton* btn = new TextButton{"play"};

            String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked (Button* button) {
    int id = std::stoi(button->getComponentID().toStdString());
    std::cout << "[PlaylistComponent::buttonClicked] button pressed: " << songs[id].name << std::endl;
    // take the path, send to player to play
    player1.loadSong(songs[id].path);
}



bool PlaylistComponent::isInterestedInFileDrag (const StringArray &files) {
    return true;
}

void PlaylistComponent::filesDropped (const StringArray &files, int x, int y) {
    std::cout << "[PlaylistComponent::filesDropped] file dropped" << std::endl;
    if (files.size() == 1) {
        // TODO: get song name from file name
        std::string path = files[0].toStdString();
        std::string name = SongInfo::getNameFromFile(path);
        SongInfo song{name, File{path}};
        songs.push_back(song);
    }
    // Update the list to be rerendered
    tableComponent.updateContent();
}
