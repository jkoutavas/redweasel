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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PreviewComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PreviewComponent::PreviewComponent (const Image& image)
    : imageComponent(new ImageComponent)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (imageComponent = new ImageComponent());
    imageComponent->setName ("imageComponent");


    //[UserPreSize]
    setImage(image);
    imageComponent->setImagePlacement(RectanglePlacement::stretchToFit);
    //[/UserPreSize]


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PreviewComponent::~PreviewComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    imageComponent = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PreviewComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PreviewComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    imageComponent->setBounds (0, 0, 1200, 800);
    //[UserResized] Add your own custom resize handling here..
    imageComponent->setBounds (0, 0, getWidth(), getHeight());
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void
PreviewComponent::setImage(const Image& image)
{
    imageComponent->setImage(image);
    imageComponent->setSize(image.getWidth(),image.getHeight());
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PreviewComponent" componentName=""
                 parentClasses="public Component" constructorParams="const Image&amp; image"
                 variableInitialisers="imageComponent(new ImageComponent)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="1200" initialHeight="800">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="imageComponent" id="2b7e824bd4e3c69f" memberName="imageComponent"
                    virtualName="" explicitFocusOrder="0" pos="0 0 1200 800" class="ImageComponent"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
