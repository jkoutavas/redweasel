#include "HNDialogWindow.h"

//#include "FLLookAndFeelConstants.h"

HNDialogWindow*
HNDialogWindow::showDialog(const String& dialogTitle,
						   Component* componentToCentreAround,
						   Component* contentComponent,
						   bool ownsContent,
						   int closeCommandID,
                           bool modal)
{
	DialogWindow::LaunchOptions o;
	o.dialogTitle = dialogTitle;
	if( ownsContent )
		o.content.setOwned(contentComponent);
	else
		o.content.setNonOwned(contentComponent);
	o.componentToCentreAround = componentToCentreAround;
	o.escapeKeyTriggersCloseButton = true;
	o.useNativeTitleBar = true;
	o.resizable = false;
	o.useBottomRightCornerResizer = false;

	HNDialogWindow* const d = new HNDialogWindow(o,closeCommandID);
    if( modal ) {
        d->enterModalState(true, nullptr, true);
    } else {
        d->setVisible(true);
    }
    
    contentComponent->grabKeyboardFocus();

    return d;
}

HNDialogWindow::HNDialogWindow(LaunchOptions& options, int closeCommandID_)
    : DialogWindow (options.dialogTitle, options.dialogBackgroundColour,
                    options.escapeKeyTriggersCloseButton, true)
    , contentComponent(options.content.get())
    , parent(options.componentToCentreAround)
    , closeCommandID(closeCommandID_)
    , wasCanceled(false)
{
    setUsingNativeTitleBar(options.useNativeTitleBar);

    if( options.content.willDeleteObject() ) {
        setContentOwned (options.content.release(), true);
    } else {
        setContentNonOwned (options.content.release(), true);
    }
    
    centreAroundComponent(options.componentToCentreAround, getWidth(), getHeight());
    setResizable(options.resizable, options.useBottomRightCornerResizer);
}

void
HNDialogWindow::closeButtonPressed()
{
   closeButtonPressed(true);
}

void
HNDialogWindow::closeButtonPressed(bool canceled)
{
    wasCanceled = canceled;

    parent->postCommandMessage(closeCommandID);
}

void
HNDialogWindow::inputAttemptWhenModal()
{
    ModalComponentManager::getInstance()->bringModalComponentsToFront();
}

void
HNDialogWindow::paint(Graphics& g)
{
    DialogWindow::paint (g);

    g.drawImage(background,0,24,getWidth(),getHeight(),
        (background.getWidth()-getWidth())/2,(background.getHeight()-getHeight())/2,
        getWidth(),getHeight(),false);
    
    if (resizableBorder == nullptr)
    {
        g.setColour (getBackgroundColour().overlaidWith (Colour (0x80000000)));

        const BorderSize<int> border (getBorderThickness());

        g.fillRect (0, 0, getWidth(), border.getTop());
        g.fillRect (0, border.getTop(), border.getLeft(), getHeight() - border.getTopAndBottom());
        g.fillRect (getWidth() - border.getRight(), border.getTop(), border.getRight(), getHeight() - border.getTopAndBottom());
        g.fillRect (0, getHeight() - border.getBottom(), getWidth(), border.getBottom());
    }
 
    const Rectangle<int> titleBarArea (getTitleBarArea());
    g.reduceClipRegion (titleBarArea);
    g.setOrigin (titleBarArea.getX(), titleBarArea.getY());

    int titleSpaceX1 = 6;
    int titleSpaceX2 = titleBarArea.getWidth() - 6;
    getLookAndFeel().drawDocumentWindowTitleBar (*this, g,
                                                 titleBarArea.getWidth(),
                                                 titleBarArea.getHeight(),
                                                 titleSpaceX1,
                                                 jmax (1, titleSpaceX2 - titleSpaceX1),
                                                 0,
                                                 false);
 }
