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
 #include "HNWindow.h"

#include "AppProperties.h"

HNWindow::HNWindow(const String title,
                   Component *host_,
                   Component *content,
                   int closeCommandID_,
                   const String windowStateKey_)
    : DocumentWindow(title, Colours::darkgrey, DocumentWindow::closeButton)
    , host(host_)
    , windowStateKey(windowStateKey_)
    , closeCommandID(closeCommandID_)
{
    centreWithSize(content->getWidth(), content->getHeight());
    
    if( !windowStateKey.isEmpty() )
    {
        AppProperties *props = AppProperties::getInstance();
        restoreWindowStateFromString(props->getValue(windowStateKey));
    }
    
    setVisible(true);

    setContentOwned(content, false);
}

HNWindow::~HNWindow()
{
    if( !windowStateKey.isEmpty() )
    {
        AppProperties *props = AppProperties::getInstance();
        props->setValue(windowStateKey, getWindowStateAsString());
    }
}

void
HNWindow::closeButtonPressed()
{
    host->postCommandMessage(closeCommandID);
}

bool
HNWindow::keyPressed (const KeyPress& key)
{
    if( key.getTextCharacter() == 'x' )
    {
        closeButtonPressed();
        return true;
    }

    return DocumentWindow::keyPressed(key);
}
