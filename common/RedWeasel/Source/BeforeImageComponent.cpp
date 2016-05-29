/*
  ==============================================================================

    BeforeImageComponent.cpp
    Created: 29 May 2016 3:33:38am
    Author:  Jay Koutavas

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "BeforeImageComponent.h"

//==============================================================================
BeforeImageComponent::BeforeImageComponent()
    : dragEntered(false)
{
}

BeforeImageComponent::~BeforeImageComponent()
{
}

void BeforeImageComponent::paint (Graphics& g)
{
    if( getImage().isValid() )
    {
        ImageComponent::paint(g);
        return;
    }
    
    g.fillAll (Colours::white);   // clear the background

    g.setColour(dragEntered ? Colours::green : Colours::grey);
    g.drawRect (getLocalBounds(), dragEntered ? 2 : 1);

    g.setColour (Colours::lightblue);
    g.setFont (23.0f);
    g.drawText ("Open an image file or drop image here", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void BeforeImageComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

#if 0
#pragma mark - FileDragAndDropTarget
#endif

bool
BeforeImageComponent::isInterestedInFileDrag (const StringArray& files)
{
    if( files.size() != 1 ) {
        return false;
    }
    
    return ImageFileFormat::findImageFormatForFileExtension(files[0]);
}

void
BeforeImageComponent::fileDragEnter (const StringArray& files, int x, int y)
{
    dragEntered = true;
    repaint();
}

void
BeforeImageComponent::fileDragExit (const StringArray& files)
{
    dragEntered = false;
    repaint();
}

void
BeforeImageComponent::filesDropped (const StringArray& files, int x, int y)
{
    droppedFileName = files[0];
}

