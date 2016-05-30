/*
  ==============================================================================

    ImageEditorModel.cpp
    Created: 29 May 2016 4:41:06pm
    Author:  Jay Koutavas

  ==============================================================================
*/

#include "ImageEditorModel.h"

juce_ImplementSingleton(ImageEditorModel);


String
ImageEditorModel::formSaveFileName()
{
   const File sourceFile(beforeImageFullPathName.getValue());
   
   return sourceFile.getFileNameWithoutExtension()
            + "_adjusted"
            + sourceFile.getFileExtension();
}

String
ImageEditorModel::formSaveFileFullPathName()
{
    const File sourceFile(beforeImageFullPathName.getValue());
    const File parentDir = sourceFile.getParentDirectory();
    
    return parentDir.getFullPathName() + "/" + formSaveFileName();
}

bool
ImageEditorModel::saveImageFile(const File& file, const Image& image)
{
    const File sourceFile(beforeImageFullPathName.getValue());
    ImageFileFormat* format = ImageFileFormat::findImageFormatForFileExtension(sourceFile);
    bool result = format != nullptr;
    
    if( result )
    {
        if( file.exists() ) {
            file.deleteFile();
        }
        
        // create a temporary image file for the drag
        FileOutputStream stream(file);
        format->writeImageToStream(image, stream);
    }
    
    return result;
}