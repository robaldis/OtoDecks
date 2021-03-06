/*
  ==============================================================================

    PlaylistComponent.h
    Created: 20 Feb 2021 4:59:16pm
    Author:  robert

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "SongInfo.h"
#include "DeckGUI.h"

//==============================================================================
/*
*/
class PlaylistComponent    : public Component,
                             public TableListBoxModel,
                             public Button::Listener,
                             public TextEditor::Listener,
                             public FileDragAndDropTarget
{
public:
    PlaylistComponent(DeckGUI &player1, DeckGUI &player2);
    ~PlaylistComponent();

    void paint (Graphics&) override;
    void resized() override;

    /** returns the vector that the TableListBox is supposed to be rendering,
     * this is how many rows there will be on the TableListBox*/
    int getNumRows() override;
    /** Renders the background of a row of the table */
    void paintRowBackground (Graphics &, int rowNumber, int width, int height, bool rowIsSelected) override;
    /** Renders the cell */
    void paintCell (Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell	(int rowNumber, int	columnId, bool isRowSelected, Component * existingComponentToUpdate) override;	
    
    // -- Button::Listener overrides --
    /** calls every time a button is pressed */
    void buttonClicked (Button* button) override;

    /** Called when the text is changed in the textEditor*/
    void textEditorTextChanged(TextEditor& editor) override;


    /** FileDragAndDrop override, triggers when a file hovers over this component */
    bool isInterestedInFileDrag (const StringArray &files) override;
    /** FileDragAndDrop override, triggers when a file is drop into the component */
    void filesDropped (const StringArray &files, int x, int y) override;

    /** Adds an entry of Song to the songs vector */
    void addToSongs(std::string);
    /** remove from the songs array */
    void removeFromSongs(int id);


private:
    /** save the songs vector to csv file */
    void saveToFile();
    /** Load songs from csv file */
    void loadFromFile();
    void filterSongs();

    DeckGUI &player1;
    DeckGUI &player2;

    AudioFormatManager formatManager;

    bool searching;
    std::string searchQuery;

    TextEditor search;
    TextButton load{"Load"};

    TableListBox tableComponent;
    std::vector<SongInfo> songs;
    std::vector<SongInfo> songsFilter;
    std::vector<std::string> songTitle;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
