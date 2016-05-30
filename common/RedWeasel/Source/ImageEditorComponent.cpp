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

#include "ImageEditorComponent.h"

#include "ImageEditorModel.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ImageEditorComponent::ImageEditorComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (redSlider = new Slider ("redSlider"));
    redSlider->setRange (-50, 50, 1);
    redSlider->setSliderStyle (Slider::LinearHorizontal);
    redSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 20);
    redSlider->addListener (this);

    addAndMakeVisible (greenSlider = new Slider ("greenSlider"));
    greenSlider->setRange (-50, 50, 1);
    greenSlider->setSliderStyle (Slider::LinearHorizontal);
    greenSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 20);
    greenSlider->addListener (this);

    addAndMakeVisible (blueSlider = new Slider ("blueSlider"));
    blueSlider->setRange (-50, 50, 1);
    blueSlider->setSliderStyle (Slider::LinearHorizontal);
    blueSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 20);
    blueSlider->addListener (this);

    addAndMakeVisible (beforeImageView = new BeforeImageComponent());
    beforeImageView->setName ("beforeImageView");

    addAndMakeVisible (afterImageView = new AfterImageComponent());
    afterImageView->setName ("afterImageView");

    addAndMakeVisible (redLabel = new Label ("redLabel",
                                             TRANS("Red")));
    redLabel->setFont (Font (15.00f, Font::plain));
    redLabel->setJustificationType (Justification::centredRight);
    redLabel->setEditable (false, false, false);
    redLabel->setColour (TextEditor::textColourId, Colours::black);
    redLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (greenLanel = new Label ("greenLabel",
                                               TRANS("Green")));
    greenLanel->setFont (Font (15.00f, Font::plain));
    greenLanel->setJustificationType (Justification::centredRight);
    greenLanel->setEditable (false, false, false);
    greenLanel->setColour (TextEditor::textColourId, Colours::black);
    greenLanel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (blueLabel = new Label ("blueLabel",
                                              TRANS("Blue\n")));
    blueLabel->setFont (Font (15.00f, Font::plain));
    blueLabel->setJustificationType (Justification::centredRight);
    blueLabel->setEditable (false, false, false);
    blueLabel->setColour (TextEditor::textColourId, Colours::black);
    blueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1030, 490);


    //[Constructor] You can add your own custom stuff here..

//    beforeImageView->setImage(ImageCache::getFromMemory(BinaryData::RedWeasel_jpeg, BinaryData::RedWeasel_jpegSize));
    adjustRGB();

    ImageEditorModel::getInstance()->beforeImageFullPathName.addListener(this);

    //[/Constructor]
}

ImageEditorComponent::~ImageEditorComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    redSlider = nullptr;
    greenSlider = nullptr;
    blueSlider = nullptr;
    beforeImageView = nullptr;
    afterImageView = nullptr;
    redLabel = nullptr;
    greenLanel = nullptr;
    blueLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ImageEditorComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ImageEditorComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    redSlider->setBounds (568, 329, 450, 24);
    greenSlider->setBounds (568, 369, 450, 24);
    blueSlider->setBounds (568, 409, 450, 24);
    beforeImageView->setBounds (8, 12, 500, 300);
    afterImageView->setBounds (520, 12, 500, 300);
    redLabel->setBounds (522, 330, 38, 24);
    greenLanel->setBounds (505, 368, 54, 24);
    blueLabel->setBounds (521, 408, 38, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ImageEditorComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == redSlider)
    {
        //[UserSliderCode_redSlider] -- add your slider handling code here..
        adjustRGB();
        //[/UserSliderCode_redSlider]
    }
    else if (sliderThatWasMoved == greenSlider)
    {
        //[UserSliderCode_greenSlider] -- add your slider handling code here..
        adjustRGB();
        //[/UserSliderCode_greenSlider]
    }
    else if (sliderThatWasMoved == blueSlider)
    {
        //[UserSliderCode_blueSlider] -- add your slider handling code here..
        adjustRGB();
        //[/UserSliderCode_blueSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

static uint8 adjust(uint8 color, double percent)
{
    const int result = color + 255 * percent;

    return std::max(std::min(result,255),0);
}

void
ImageEditorComponent::adjustRGB()
{
    const bool haveImage = beforeImageView->getImage().isValid();

    redSlider->setEnabled(haveImage);
    greenSlider->setEnabled(haveImage);
    blueSlider->setEnabled(haveImage);
    
    if( !haveImage ) {
        return;
    }
    
    // values are from -50 to 50 with 0 being normal
    // 0 results in no change
    // -50 results in -50%
    // +50 results in +50%
    const double redPercent = redSlider->getValue()/100.0;
    const double greenPercent = greenSlider->getValue()/100.0;
    const double bluePercent = blueSlider->getValue()/100.0;

    Image afterImage = beforeImageView->getImage();
    afterImage.duplicateIfShared();
    for( int x=0; x<afterImage.getWidth(); ++x ) {
        for( int y=0; y<afterImage.getHeight(); ++y )
        {
            const Colour pixel(afterImage.getPixelAt(x, y));
            afterImage.setPixelAt(x, y, Colour(adjust(pixel.getRed(), redPercent),
                                               adjust(pixel.getGreen(), greenPercent),
                                               adjust(pixel.getBlue(), bluePercent)));
        }
    }
    afterImageView->setImage(afterImage);
}

void
ImageEditorComponent::loadImageFile(const File& file)
{
    beforeImageView->setImage(ImageFileFormat::loadFrom(file));
    adjustRGB();
}

void
ImageEditorComponent::saveImageFile(const File& file)
{
   ImageEditorModel::getInstance()->saveImageFile(file, afterImageView->getImage());
}

#if 0
#pragma mark - Value::Listener
#endif

void
ImageEditorComponent::valueChanged(Value &value)
{
    if( value.refersToSameSourceAs(ImageEditorModel::getInstance()->beforeImageFullPathName) )
    {
        File f(value.getValue());
        loadImageFile(f);
    }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ImageEditorComponent" componentName=""
                 parentClasses="public Component, public Value::Listener" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="1030" initialHeight="490">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="redSlider" id="bdb7303b5032438b" memberName="redSlider"
          virtualName="" explicitFocusOrder="0" pos="568 329 450 24" min="-50"
          max="50" int="1" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="greenSlider" id="436a5ff4bb288b22" memberName="greenSlider"
          virtualName="" explicitFocusOrder="0" pos="568 369 450 24" min="-50"
          max="50" int="1" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="blueSlider" id="98f2f7171ee398f0" memberName="blueSlider"
          virtualName="" explicitFocusOrder="0" pos="568 409 450 24" min="-50"
          max="50" int="1" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <GENERICCOMPONENT name="beforeImageView" id="fae0b48cffc5c30a" memberName="beforeImageView"
                    virtualName="" explicitFocusOrder="0" pos="8 12 500 300" class="BeforeImageComponent"
                    params=""/>
  <GENERICCOMPONENT name="afterImageView" id="3df6bb30ea2d0e1e" memberName="afterImageView"
                    virtualName="" explicitFocusOrder="0" pos="520 12 500 300" class="AfterImageComponent"
                    params=""/>
  <LABEL name="redLabel" id="935403b992fdd1" memberName="redLabel" virtualName=""
         explicitFocusOrder="0" pos="522 330 38 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Red" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <LABEL name="greenLabel" id="fff9a69e7f26bb1f" memberName="greenLanel"
         virtualName="" explicitFocusOrder="0" pos="505 368 54 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Green" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <LABEL name="blueLabel" id="9f5edce0b62335fe" memberName="blueLabel"
         virtualName="" explicitFocusOrder="0" pos="521 408 38 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Blue&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
