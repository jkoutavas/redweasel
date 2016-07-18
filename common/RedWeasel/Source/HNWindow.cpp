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
        AppProperties *properties = AppProperties::getInstance();
        restoreWindowStateFromString(properties->getValue(windowStateKey));
    }
    
    setVisible(true);

    setContentOwned(content, false);
}

HNWindow::~HNWindow()
{
    if( !windowStateKey.isEmpty() )
    {
        AppProperties *properties = AppProperties::getInstance();
        properties->setValue(windowStateKey, getWindowStateAsString());
    }
}

void
HNWindow::closeButtonPressed()
{
    host->postCommandMessage(closeCommandID);
}
