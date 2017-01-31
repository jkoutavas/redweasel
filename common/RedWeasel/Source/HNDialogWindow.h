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
 
#ifndef HNDIALOGWINDOW_H_INCLUDED
#define HNDIALOGWINDOW_H_INCLUDED

#include "JuceHeader.h"

class HNDialogWindow : public DialogWindow
{
public:
	static HNDialogWindow* showDialog(const String& dialogTitle,
									Component* componentToCentreAround,
									Component* contentComponent,
									bool ownsContent,
									int closeCommandID,
                                    bool modal=true);
    

public:
    HNDialogWindow(LaunchOptions& options, int closeCommandID);
    
    void closeButtonPressed(bool canceled);
    Component* getContentComponent() const { return contentComponent; }
    bool getWasCanceled() const { return wasCanceled; }

public: // DialogWindow
    void closeButtonPressed();
	void inputAttemptWhenModal();
    virtual void paint(Graphics& g);

private:
    JUCE_DECLARE_NON_COPYABLE (HNDialogWindow);

private:
    Image       background;
    Component*  contentComponent;
	Component*	parent;

private:
	int			closeCommandID;
    bool        wasCanceled;
};


#endif  // FLDIALOGWINDOW_H_INCLUDED
