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

#ifndef BEFOREIMAGECCOMPONENT_H_INCLUDED
#define BEFOREIMAGECCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class BeforeImageComponent
    : public ImageComponent
    , public FileDragAndDropTarget
{
public:
    class DropMessage : public Message
    {
    public:
        DropMessage(String filename_) : filename(filename_) {;}
        String filename;
    };
    
public:
    BeforeImageComponent();
    ~BeforeImageComponent();

    void paint (Graphics&);
    void resized();

public: // FileDragAndDropTarget
    virtual bool isInterestedInFileDrag (const StringArray& files);
    virtual void fileDragEnter (const StringArray& files, int x, int y);
    virtual void fileDragExit (const StringArray& files);
    virtual void filesDropped (const StringArray& files, int x, int y);

private:
    bool dragEntered;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BeforeImageComponent)
};


#endif  // BEFOREIMAGECOMPONENT_H_INCLUDED
