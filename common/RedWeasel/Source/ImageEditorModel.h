/*
  ==============================================================================

    ImageEditorModel.h
    Created: 29 May 2016 4:41:06pm
    Author:  Jay Koutavas

  ==============================================================================
*/

#ifndef IMAGEEDITORMODEL_H_INCLUDED
#define IMAGEEDITORMODEL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class ImageEditorModel
{
public:
	juce_DeclareSingleton(ImageEditorModel, true);
    
    ImageEditorModel() {;}
    ~ImageEditorModel() {;}
    
public:
    String formSaveFileName();
    String formSaveFileFullPathName();
    bool saveImageFile(const File& file, const Image& image);
    
public:
    Value beforeImageFullPathName;
};

#endif  // IMAGEEDITORMODEL_H_INCLUDED
