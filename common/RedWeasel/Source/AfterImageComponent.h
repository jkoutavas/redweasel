/*
  ==============================================================================

    AfterImageComponent.h
    Created: 29 May 2016 5:31:25am
    Author:  Jay Koutavas

  ==============================================================================
*/

#ifndef AFTERIMAGECOMPONENT_H_INCLUDED
#define AFTERIMAGECOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class AfterImageComponent
    : public ImageComponent
    , public DragAndDropContainer
{
public:
    AfterImageComponent();
    ~AfterImageComponent();

public: // Component
    void paint (Graphics&) override;
    void resized() override;

    void mouseDown(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e) override;

public: // DragAndDropContainer
    bool shouldDropFilesWhenDraggedExternally (const DragAndDropTarget::SourceDetails& sourceDetails,
                                                       StringArray& files, bool& canMoveFiles) override;

private:
    File tempSavedFile;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AfterImageComponent)
};


#endif  // AFTERIMAGECOMPONENT_H_INCLUDED
