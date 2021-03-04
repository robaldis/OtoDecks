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
                             public FileDragAndDropTarget
{
public:
    PlaylistComponent(DeckGUI &player1, DeckGUI &player2);
    ~PlaylistComponent();

    void paint (Graphics&) override;
    void resized() override;

    // -- TableListBoxModel overrides --
    int getNumRows() override;
    void paintRowBackground (Graphics &, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell (Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell	(int rowNumber, int	columnId, bool isRowSelected, Component * existingComponentToUpdate) override;	
    
    // -- Button::Listener overrides --
    void buttonClicked (Button* button) override;

    bool isInterestedInFileDrag (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override;

private:
    DeckGUI &player1;
    DeckGUI &player2;

    TableListBox tableComponent;
    std::vector<SongInfo> songs;
    std::vector<std::string> songTitle;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
