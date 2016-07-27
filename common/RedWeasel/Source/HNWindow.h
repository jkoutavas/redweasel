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
    void closeButtonPressed() override;

    bool keyPressed (const KeyPress& key) override;

private:
    Component           *host;
    String              windowStateKey;
    int                 closeCommandID;
};

#endif  // HNWINDOW_H_INCLUDED
