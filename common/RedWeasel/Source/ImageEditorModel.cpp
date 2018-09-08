/********************************************************************************
 *   _    _                                                                     *
 *  | |  | |                                             Copyright 2017         *
 *  | |__| |   ___   _   _   _ __     ___   __      __   Heynow Software, LLC   *
 *  |  __  |  / _ \ | | | | | '_ \   / _ \  \ \ /\ / /                          *
 *  | |  | | |  __/ | |_| | | | | | | (_) |  \ V  V /                           *
 *  |_|  |_|  \___|  \__, | |_| |_|  \___/    \_/\_/                            *
 *                    __/ |                                                     *
 *                   |___/  S  O  F  T  W  A  R  E                              *
 *                                                                              *
 *  author: Jay Koutavas                                                        *
 *  email: jay@heynow.com                                                       *
 *                                                                              *
 *  This file is part of the "Red Weasel" application.  This application is     *
 *  free software; you can redistribute it and/or modify it under the terms     *
 *  of the GNU General Public License as published by the Free Software         *
 *  Foundation; either version 3, or (at your option) any later version.        *
 *                                                                              *
 *  This application is distributed in the hope that it will be useful, but     *
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  *
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    *
 *  for more details.                                                           *
 *                                                                              *
 *  You should have received a copy of the GNU General Public License along     *
 *  with this application's source code; see the file COPYING. If not, see      *
 *  <http://www.gnu.org/licenses/>.                                             *
 *                                                                              *
 ********************************************************************************/
 
#include "ImageEditorModel.h"

juce_ImplementSingleton(ImageEditorModel);


String
ImageEditorModel::formSaveFileName()
{
   const File sourceFile(beforeImageFullPathName.getValue());
   
   return sourceFile.getFileNameWithoutExtension()
            + kOutputImageSuffix
            + sourceFile.getFileExtension();
}

String
ImageEditorModel::formSaveFileFullPathName()
{
    const File sourceFile(beforeImageFullPathName.getValue());
    const File parentDir = sourceFile.getParentDirectory();
    
    return parentDir.getFullPathName() + File::getSeparatorString() + formSaveFileName();
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
