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
