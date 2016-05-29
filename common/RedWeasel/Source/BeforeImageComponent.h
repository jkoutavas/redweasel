/*
  ==============================================================================

    BeforeImageComponent.h
    Created: 29 May 2016 3:33:38am
    Author:  Jay Koutavas

  ==============================================================================
*/

#ifndef BEFOREIMAGECCOMPONENT_H_INCLUDED
#define BEFOREIMAGECCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class BeforeImageComponent
    : public ImageComponent
    , public FileDragAndDropTarget
{
public:
    class DropMessage : public Message
    {
    public:
        DropMessage(String filename_) : filename(filename_) {;}
        String filename;
    };
    
public:
    BeforeImageComponent();
    ~BeforeImageComponent();

    void paint (Graphics&);
    void resized();

public: // FileDragAndDropTarget
    virtual bool isInterestedInFileDrag (const StringArray& files);
    virtual void fileDragEnter (const StringArray& files, int x, int y);
    virtual void fileDragExit (const StringArray& files);
    virtual void filesDropped (const StringArray& files, int x, int y);
    
public:
    Value droppedFileName;

private:
    bool dragEntered;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BeforeImageComponent)
};


#endif  // BEFOREIMAGECOMPONENT_H_INCLUDED
