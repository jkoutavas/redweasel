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
                              public Timer,
                              public Value::Listener,
                              public SliderListener
{
public:
    //==============================================================================
    ImageEditorComponent ();
    ~ImageEditorComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    // Timer
    void timerCallback() override;

    // Value::Listener
    void valueChanged(Value &value) override;

    // our stuff
    Image adjustRGB(bool rescale=true);
    void loadImageFile(const File& file);
    void saveImageFile(const File& file);
    void scaleBoundsForComponent(Component* c);
    void shiftXYPositionForComponent(Component* c);
    void shiftYPositionForComponent(Component* c);

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    bool keyPressed (const KeyPress& key) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Array<File> inputFiles;
    int inputFileIndex;

    // override the fileSelector's look and feel so that its buttons to get
    // keyboard focus
    class FileSelectorLookAndFeel : public LookAndFeel_V2
    {
        Button* createSliderButton (Slider&, const bool isIncrement)
        {
            TextButton *button = new TextButton (isIncrement ? "+" : "-", String::empty);

            button->setWantsKeyboardFocus(false); // we overrode look and feel to get this

            return button;
        }
    };
    FileSelectorLookAndFeel fileSelectorLookAndFeel;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> redSlider;
    ScopedPointer<Slider> greenSlider;
    ScopedPointer<Slider> blueSlider;
    ScopedPointer<BeforeImageComponent> beforeImageView;
    ScopedPointer<AfterImageComponent> afterImageView;
    ScopedPointer<Label> redLabel;
    ScopedPointer<Label> greenLabel;
    ScopedPointer<Label> blueLabel;
    ScopedPointer<Label> fileLabel;
    ScopedPointer<Slider> fileSelector;
    ScopedPointer<Label> helpLabel;
    ScopedPointer<Label> helpLabel2;
    ScopedPointer<Label> saveMessageLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImageEditorComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_1EB5247756C0C4F2__
