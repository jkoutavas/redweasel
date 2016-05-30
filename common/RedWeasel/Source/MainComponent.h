/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "ImageEditorComponent.h"

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

private: // our stuff
    void openAboutDialog();
    void openImageFile();
    void saveImageFile();
    
private:
    ApplicationCommandManager appCommandManager;
    DocumentWindow *documentWindow;
    ImageEditorComponent imageEditor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

#endif  // MAINCOMPONENT_H_INCLUDED
