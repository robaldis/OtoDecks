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

//==============================================================================
/*
*/
class PlaylistComponent    : public Component,
                             public TableListBoxModel,
                             public Button::Listener
{
public:
    PlaylistComponent();
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

private:

    TableListBox tableComponent;
    std::vector<std::string> songTitle;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
