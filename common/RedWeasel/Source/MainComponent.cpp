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

#include "MainComponent.h"

#include "AboutComponent.h"
#include "AppProperties.h"
#include "ImageEditorModel.h"
#include "PreviewComponent.h"

enum {
    eAboutClosedCmdID = 1000,
	eAboutOpenCmdID,
    eFileOpenCmdID,
    eFileSaveAsCmdID,
    ePreviewCmdID,
    ePreviewClosedCmdID,
};

static String aboutMenuItemTitle()
{
    return "About " + JUCEApplication::getInstance()->getApplicationName() + "...";
}

MainContentComponent::MainContentComponent()
    : previewComponent(nullptr)
    , previewWindow(nullptr)
{
    auto& lf = dynamic_cast<LookAndFeel_V4&>(getLookAndFeel());
    lf.setColourScheme(LookAndFeel_V4::getLightColourScheme());

    appCommandManager.registerAllCommandsForTarget(this);
    setApplicationCommandManagerToWatch(&appCommandManager);
    appCommandManager.setFirstCommandTarget(this);

#if JUCE_MAC
	PopupMenu pop;
	pop.addItem(eAboutOpenCmdID, aboutMenuItemTitle());
 	MenuBarModel::setMacMainMenu(this, &pop);
#endif

#if JUCE_WINDOWS
    menuBar = new MenuBarComponent(this);
    addAndMakeVisible(menuBar);
#endif

    addAndMakeVisible(imageEditor);

    ImageEditorModel::getInstance()->beforeImageFullPathName.addListener(this);

    int height = 515;
#if JUCE_WINDOWS
    height += lf.getDefaultMenuBarHeight();
#endif

    setSize(1030, height);

#if JUCE_WINDOWS
	imageEditor.setTopLeftPosition(imageEditor.getX(), imageEditor.getY() + lf.getDefaultMenuBarHeight());
#endif
}

MainContentComponent::~MainContentComponent()
{
#if JUCE_MAC
	MenuBarModel::setMacMainMenu(nullptr);
#endif
    setApplicationCommandManagerToWatch(nullptr);
}

#if 0
#pragma mark - Component
#endif

void
MainContentComponent::handleCommandMessage(int commandId)
{
    switch( commandId )
    {
        case eAboutClosedCmdID:
            aboutDialog = nullptr;
        break;

        case ePreviewClosedCmdID:
            AppProperties::getInstance()->setValue("PreviewWindowPos",
                previewWindow->getWindowStateAsString());
            previewWindow = nullptr;
            previewComponent = nullptr;
        break;
    }
}

void
MainContentComponent::resized()
{
#if JUCE_WINDOWS
	menuBar->setBounds(0, 0, getWidth(), getLookAndFeel().getDefaultMenuBarHeight());
#endif

    imageEditor.setSize(getWidth(),getHeight());
}

#if 0
#pragma mark - ApplicationCommandTarget
#endif

void 
MainContentComponent::getAllCommands(Array<CommandID>& commands)
{
    // this returns the set of all commands that this target can perform
    const CommandID ids[] = {
        eAboutOpenCmdID,
        eFileOpenCmdID,
        eFileSaveAsCmdID,
        ePreviewCmdID,
#if JUCE_WINDOWS
        juce::StandardApplicationCommandIDs::quit
#endif
	};

    commands.addArray(ids, numElementsInArray(ids));
}

void 
MainContentComponent::getCommandInfo(const CommandID commandID, ApplicationCommandInfo& result)
{
    const String category("general");

    switch( commandID )
    {
		case eAboutOpenCmdID:
			result.setInfo(aboutMenuItemTitle(), "", category, 0);
		break;
        
        case eFileOpenCmdID:
            result.setInfo("Open...", "", category, 0);
            result.addDefaultKeypress('o',ModifierKeys::commandModifier);
        break;
        
        case eFileSaveAsCmdID:
            result.setInfo("Save As...", "", category, 0);
			result.setActive(ImageEditorModel::getInstance()->beforeImageFullPathName != "");
            result.addDefaultKeypress('s',ModifierKeys::commandModifier);
        break;

        case ePreviewCmdID:
            result.setInfo("Preview Window", "", category, 0);
			result.setActive(ImageEditorModel::getInstance()->beforeImageFullPathName != "");
            result.addDefaultKeypress('x',ModifierKeys::noModifiers);
        break;
        
#if JUCE_WINDOWS
        case juce::StandardApplicationCommandIDs::quit:
            result.setInfo("Quit", "", category, 0);
            result.addDefaultKeypress('q',ModifierKeys::commandModifier);
        break;
#endif
    }
}

ApplicationCommandTarget*
MainContentComponent::getNextCommandTarget()
{
    return nullptr;
}

bool
MainContentComponent::perform(const InvocationInfo& info)
{
   switch( info.commandID )
    {
#if JUCE_WINDOWS
        case eAboutOpenCmdID:
            openAboutDialog();
        break;
        
        case juce::StandardApplicationCommandIDs::quit:
			JUCEApplication::quit();
        break;
#endif

        case eFileOpenCmdID:
            openImageFile();
        break;
        
        case eFileSaveAsCmdID:
            saveImageFile();
        break;
        
        case ePreviewCmdID:
            openImagePreviewWindow();
        break;
    }

    return true;
}

#if 0
#pragma mark - MenuBarModel
#endif

StringArray
MainContentComponent::getMenuBarNames()
{
	StringArray names;

#if JUCE_WINDOWS
	names.add(JUCEApplication::getInstance()->getApplicationName());
#endif

    names.add("File");
    names.add("View");
    
	return names;
}

PopupMenu 
MainContentComponent::getMenuForIndex(int /*topLevelMenuIndex*/, const String& menuName)
{
    PopupMenu menu;

#if JUCE_WINDOWS
    if( menuName == JUCEApplication::getInstance()->getApplicationName() ) {
        menu.addCommandItem(&appCommandManager, eAboutOpenCmdID);
    }
#endif

    if( menuName == "File" )
    {
        menu.addCommandItem(&appCommandManager, eFileOpenCmdID);
        menu.addCommandItem(&appCommandManager, eFileSaveAsCmdID);
#if JUCE_WINDOWS
        menu.addSeparator();
        menu.addCommandItem(&appCommandManager, juce::StandardApplicationCommandIDs::quit);
#endif
    }

    if( menuName == "View" )
    {
        menu.addCommandItem(&appCommandManager, ePreviewCmdID);
    }
    
    return menu;
}

void
MainContentComponent::menuItemSelected(int menuItemID, int /*topLevelMenuIndex*/)
{
#if JUCE_MAC
    switch( menuItemID )
    {
        case eAboutOpenCmdID:
            openAboutDialog();
        break;

        default:
        break;
    }
#endif
}

#if 0
#pragma mark - Value::Listener
#endif

void
MainContentComponent::valueChanged(Value &value)
{
    if( value.refersToSameSourceAs(ImageEditorModel::getInstance()->beforeImageFullPathName) )
    {
        // tear down current preview window if open
        if( previewWindow ) {
            handleCommandMessage(ePreviewClosedCmdID);
        }
        menuItemsChanged(); // light-up the 'Save As...' menu item
    }
}

#if 0
#pragma mark - our stuff
#endif

void
MainContentComponent::openAboutDialog()
{
    if( aboutDialog )
    {
        aboutDialog->toFront(true);
        return;
    }
    
    aboutDialog = HNDialogWindow::showDialog("About "+JUCEApplication::getInstance()->getApplicationName(),
        this, new AboutComponent, true, eAboutClosedCmdID);
}

void
MainContentComponent::openImageFile()
{
    String lastOpenedFolder = AppProperties::getInstance()->getValue("lastOpenedFolder");
    File folder(lastOpenedFolder);
    if( !folder.exists() ) {
        folder = File::getSpecialLocation(File::userPicturesDirectory);
    }
    
    FileChooser fc("Choose an image to adjust", folder, kImageWildcardPattern);
    if( fc.browseForFileToOpen() )
    {
        folder = fc.getResult().getParentDirectory();
        AppProperties::getInstance()->setValue("lastOpenedFolder",folder.getFullPathName());
        ImageEditorModel::getInstance()->beforeImageFullPathName = fc.getResult().getFullPathName();
    }
}
void
MainContentComponent::openImagePreviewWindow()
{
    const Image fullImage = imageEditor.adjustRGB(false);

    if( previewWindow )
    {
        previewWindow->toFront(true);
        previewComponent->setImage(fullImage);
    }
    else
    {
        previewComponent = new PreviewComponent(fullImage);
        previewWindow = new HNWindow("Preview",
                            this,
                            previewComponent,
                            ePreviewClosedCmdID,
                            "PreviewWindowPos");
        previewWindow->setResizable(true,true);

        Rectangle<int> area = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
        
        const double aspectRatio = fullImage.getWidth() / fullImage.getHeight();
        
        previewWindow->setSize(
            std::min(fullImage.getWidth(), area.getWidth()),
            std::min(fullImage.getHeight(), (int)(area.getHeight()/aspectRatio)));
        
        previewWindow->setResizeLimits(
            std::min(fullImage.getWidth(), area.getWidth()),
            std::min(fullImage.getHeight(), (int)(area.getHeight()/aspectRatio)),
            area.getWidth(),
            (int)(area.getHeight()/aspectRatio));
    }
}

void
MainContentComponent::saveImageFile()
{
    String filename = ImageEditorModel::getInstance()->formSaveFileFullPathName();
    FileChooser fc("Save adjusted image", filename, kImageWildcardPattern);

    if( fc.browseForFileToSave(true) ) {
        imageEditor.saveImageFile(fc.getResult());
    }
}
