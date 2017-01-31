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
#include "BeforeImageComponent.h"

#include "ImageEditorModel.h"

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
    g.fillAll (Colours::white);

    g.setColour(dragEntered ? Colours::green : Colours::lightgrey);
    g.drawRect (getLocalBounds(), dragEntered ? 2 : 1);

    if( getImage().isValid() )
    {
        ImageComponent::paint(g);
        return;
    }
    
    g.setColour (Colours::lightblue);
    g.setFont (Font(28.0f, Font::italic));
    g.drawText ("Open an image file or drop image here", getLocalBounds(),
                Justification::centred, true);
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
    
    return ImageFileFormat::findImageFormatForFileExtension(files[0]) != nullptr;
}

void
BeforeImageComponent::fileDragEnter (const StringArray& /*files*/, int /*x*/, int /*y*/)
{
    dragEntered = true;
    repaint();
}

void
BeforeImageComponent::fileDragExit (const StringArray& /*files*/)
{
    dragEntered = false;
    repaint();
}

void
BeforeImageComponent::filesDropped (const StringArray& files, int /*x*/, int /*y*/)
{
    ImageEditorModel::getInstance()->beforeImageFullPathName = files[0];
    dragEntered = false;
    repaint();
}

