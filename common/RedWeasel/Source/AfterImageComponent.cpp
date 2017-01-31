/********************************************************************************
 *   _    _                                                                     *
 *  | |  | |                                             Copyright 2017         *
 *  | |__| |   ___   _   _   _ __     ___   __      __   Heynow Software, LLC   *
 *  |  __  |  / _ \ | | | | | '_ \   / _ \  \ \ /\ / /                          *
 *  | |  | | |  __/ | |_| | | | | | | (_) |  \ V  V /                           *
 *  |_|  |_|  \___|  \__, | |_| |_|  \___/    \_/\_/                            *
 *                    __/ |                                                     *
 *                   |___/  S  O  F  T  W  A  R  E                              *
 *                                                                              *
 *  author: Jay Koutavas                                                        *
 *  email: jay@heynow.com                                                       *
 *                                                                              *
 *  This file is part of the "Red Weasel" application.  This application is     *
 *  free software; you can redistribute it and/or modify it under the terms     *
 *  of the GNU General Public License as published by the Free Software         *
 *  Foundation; either version 3, or (at your option) any later version.        *
 *                                                                              *
 *  This application is distributed in the hope that it will be useful, but     *
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  *
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    *
 *  for more details.                                                           *
 *                                                                              *
 *  You should have received a copy of the GNU General Public License along     *
 *  with this application's source code; see the file COPYING. If not, see      *
 *  <http://www.gnu.org/licenses/>.                                             *
 *                                                                              *
 ********************************************************************************/

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
    g.fillAll (Colours::white);

    g.setColour(Colours::lightgrey);
    g.drawRect (getLocalBounds(), 1);

    if( getImage().isValid() )
    {
        ImageComponent::paint(g);
        return;
    }
    
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
AfterImageComponent::mouseDown(const MouseEvent& /*e*/)
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
AfterImageComponent::mouseDrag(const MouseEvent& /*e*/)
{
    StringArray filesArray;
    
    filesArray.add(tempSavedFile.getFullPathName());
    performExternalDragDropOfFiles(filesArray, true);
}

void
AfterImageComponent::mouseUp(const MouseEvent& /*e*/)
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
AfterImageComponent::shouldDropFilesWhenDraggedExternally (const DragAndDropTarget::SourceDetails& /*sourceDetails*/,
                                                       StringArray& /*files*/, bool& /*canMoveFiles*/)
{
    return true;
}
