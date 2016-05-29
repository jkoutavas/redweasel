/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_1EB5247756C0C4F2__
#define __JUCE_HEADER_1EB5247756C0C4F2__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "AfterImageComponent.h"
#include "BeforeImageComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ImageEditorComponent  : public Component,
                              public Value::Listener,
                              public SliderListener
{
public:
    //==============================================================================
    ImageEditorComponent (DocumentWindow *documentWindow);
    ~ImageEditorComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void adjustRGB();
    void loadImageFile(const File& file);

    // Value::Listener
    void valueChanged(Value &value) override;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    DocumentWindow *documentWindow;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> redSlider;
    ScopedPointer<Slider> greenSlider;
    ScopedPointer<Slider> blueSlider;
    ScopedPointer<BeforeImageComponent> beforeImageView;
    ScopedPointer<AfterImageComponent> afterImageView;
    ScopedPointer<Label> redLabel;
    ScopedPointer<Label> greenLanel;
    ScopedPointer<Label> blueLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImageEditorComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_1EB5247756C0C4F2__
