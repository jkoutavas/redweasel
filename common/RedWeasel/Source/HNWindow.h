#ifndef HNWINDOW_H_INCLUDED
#define HNWINDOW_H_INCLUDED

#include "JuceHeader.h"

class HNWindow : public DocumentWindow
{
public:
    HNWindow(const String title,
             Component *host,
             Component *content,
             int closeCommandID,
             const String windowStateKey);
             
    ~HNWindow();

public:
    virtual void closeButtonPressed();

private:
    Component           *host;
    String              windowStateKey;
    int                 closeCommandID;
};

#endif  // HNWINDOW_H_INCLUDED
