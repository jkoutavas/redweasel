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
 
#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "HNDialogWindow.h"
#include "HNWindow.h"
#include "ImageEditorComponent.h"
#include "PreviewComponent.h"

class MainContentComponent
    : public Component
    , private ApplicationCommandTarget
	, private MenuBarModel
    , public Value::Listener
{
public:
    MainContentComponent();
    ~MainContentComponent();

public: // Component
	void handleCommandMessage(int commandId) override;
    void resized() override;

private: // ApplicationCommandTarget
    void getAllCommands(Array<CommandID>& commands) override;
    void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;
    ApplicationCommandTarget* getNextCommandTarget() override;
    bool perform(const InvocationInfo& info) override;
    
private: // MenuBarModel
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex(int topLevelMenuIndex, const String& menuName) override;
    void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

public: // Value::Listener
    void valueChanged(Value &value) override;

public: // our stuff
    ApplicationCommandManager& getApplicationCommandManager() { return appCommandManager; }
    
private: // our stuff
    void openAboutDialog();
    void openImageFile();
    void openImagePreviewWindow();
    void saveImageFile();
    
private:
    ScopedPointer<HNDialogWindow> aboutDialog;
    ApplicationCommandManager appCommandManager;
    DocumentWindow *documentWindow;
    ImageEditorComponent imageEditor;
    PreviewComponent *previewComponent;
    ScopedPointer<HNWindow> previewWindow;

#if JUCE_WINDOWS
    ScopedPointer<MenuBarComponent>	menuBar;
#endif

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

#endif  // MAINCOMPONENT_H_INCLUDED
