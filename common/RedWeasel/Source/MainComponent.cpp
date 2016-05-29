/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

enum {
    eAboutClosedCmdID = 1000,
	eAboutOpenCmdID,
    eFileOpenCmdID
};

static String aboutMenuItemTitle()
{
    return "About " + JUCEApplication::getInstance()->getApplicationName() + "...";
}

MainContentComponent::MainContentComponent()
{
    appCommandManager.registerAllCommandsForTarget(this);
    appCommandManager.setFirstCommandTarget(this);

#if JUCE_MAC
	PopupMenu pop;
	pop.addItem(eAboutOpenCmdID, aboutMenuItemTitle());
 	MenuBarModel::setMacMainMenu(this, &pop);
#endif
    
    addAndMakeVisible(imageEditor);

    setSize(1030, 450);
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
MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
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
        eFileOpenCmdID
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
			result.setInfo(aboutMenuItemTitle(), String::empty, category, 0);
		break;
        
        case eFileOpenCmdID:
            result.setInfo("Open...", String::empty, category, 0);
        break;
    }
}

ApplicationCommandTarget*
MainContentComponent::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
}

bool
MainContentComponent::perform(const InvocationInfo& /*info*/)
{
    return true;
}

#if 0
#pragma mark - MenuBarModel
#endif

StringArray
MainContentComponent::getMenuBarNames()
{
	StringArray names;

    names.add("File");
    
	return names;
}

PopupMenu 
MainContentComponent::getMenuForIndex(int /*topLevelMenuIndex*/, const String& menuName)
{
    PopupMenu menu;

    if( menuName == "File" ) {
        menu.addCommandItem(&appCommandManager, eFileOpenCmdID);
    }
    
    return menu;
}

void
MainContentComponent::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
    switch( menuItemID )
    {
        case eAboutOpenCmdID:
            openAboutDialog();
        break;
        
        case eFileOpenCmdID:
            openImageFile();
        break;
    }
}

#if 0
#pragma mark - MessageListener
#endif

#if 0
#pragma mark - our stuff
#endif

void
MainContentComponent::openAboutDialog()
{
}

void
MainContentComponent::openImageFile()
{
    FileChooser fc("Choose an image",
        File::getSpecialLocation(File::userPicturesDirectory),
		"*.png,*.jpg,*.jpeg");

    if( fc.browseForFileToOpen() ) {
        imageEditor.loadImageFile(fc.getResult());
    }
}
