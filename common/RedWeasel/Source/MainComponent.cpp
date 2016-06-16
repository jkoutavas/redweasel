/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

#include "AboutComponent.h"
#include "ImageEditorModel.h"

enum {
    eAboutClosedCmdID = 1000,
	eAboutOpenCmdID,
    eFileOpenCmdID,
    eFileSaveAsCmdID
};

static String aboutMenuItemTitle()
{
    return "About " + JUCEApplication::getInstance()->getApplicationName() + "...";
}

MainContentComponent::MainContentComponent()
{
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

    int height = 450;
#if JUCE_WINDOWS
    height += 24;
#endif

    setSize(1030, height);
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
    }
}

void
MainContentComponent::resized()
{
#if JUCE_WINDOWS
    menuBar->setBounds(0, 0, getWidth(), 24);
    imageEditor.setTopLeftPosition(imageEditor.getX(), imageEditor.getY() + 24);
 #endif
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
        eFileSaveAsCmdID
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
        
        case eFileSaveAsCmdID:
            result.setInfo("Save As...", String::empty, category, 0);
			result.setActive(ImageEditorModel::getInstance()->beforeImageFullPathName != String::empty);
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

#if JUCE_WINDOWS
	names.add(JUCEApplication::getInstance()->getApplicationName());
#endif

    names.add("File");
    
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
        
        case eFileSaveAsCmdID:
            saveImageFile();
        break;
    }
}

#if 0
#pragma mark - Value::Listener
#endif

void
MainContentComponent::valueChanged(Value &value)
{
    if( value.refersToSameSourceAs(ImageEditorModel::getInstance()->beforeImageFullPathName) ) {
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
    FileChooser fc("Choose an image to adjust", File::getSpecialLocation(File::userPicturesDirectory),
        kImageWildcardPattern);

    if( fc.browseForFileToOpen() ) {
        ImageEditorModel::getInstance()->beforeImageFullPathName = fc.getResult().getFullPathName();
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
