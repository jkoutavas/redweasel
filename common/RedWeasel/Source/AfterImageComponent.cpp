/*
  ==============================================================================

    AfterImageComponent.cpp
    Created: 29 May 2016 5:31:25am
    Author:  Jay Koutavas

  ==============================================================================
*/

#include "AfterImageComponent.h"

#include "ImageEditorModel.h"

//==============================================================================
AfterImageComponent::AfterImageComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

AfterImageComponent::~AfterImageComponent()
{
}

void
AfterImageComponent::paint (Graphics& g)
{
    if( getImage().isValid() )
    {
        ImageComponent::paint(g);
        return;
    }
    
    g.fillAll (Colours::white);

    g.setColour(Colours::lightgrey);
    g.drawRect (getLocalBounds(), 1);

    g.setColour (Colours::lightblue);
    g.setFont (Font(28.0f, Font::italic));
    g.drawText ("The adjusted image will appear here", getLocalBounds(),
                Justification::centred, true);
}

void
AfterImageComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

void
AfterImageComponent::mouseDown(const MouseEvent& e)
{
    const File sourceFile(ImageEditorModel::getInstance()->beforeImageFullPathName.getValue());
    File tempDir(File::getSpecialLocation(File::tempDirectory));
    String filename = tempDir.getFullPathName()
        + File::separatorString
        + ImageEditorModel::getInstance()->formSaveFileName();
    
    tempSavedFile = File(filename);
    
    if( ImageEditorModel::getInstance()->saveImageFile(tempSavedFile, getImage()) )
    {
        // start the drag activity
        startDragging("image drag", this);
    }
}

void
AfterImageComponent::mouseDrag(const MouseEvent& e)
{
    StringArray filesArray;
    
    filesArray.add(tempSavedFile.getFullPathName());
    performExternalDragDropOfFiles(filesArray, true);
}

void
AfterImageComponent::mouseUp(const MouseEvent& e)
{
    // the temp file is now likely copied-out to the file system. Delete it.
    if( tempSavedFile.exists() ) {
        tempSavedFile.deleteFile();
    }
    
    tempSavedFile = juce::var::null;
}

#if 0
#pragma mark - DragAndDropComponent
#endif

bool
AfterImageComponent::shouldDropFilesWhenDraggedExternally (const DragAndDropTarget::SourceDetails& sourceDetails,
                                                       StringArray& files, bool& canMoveFiles)
{
    return true;
}
