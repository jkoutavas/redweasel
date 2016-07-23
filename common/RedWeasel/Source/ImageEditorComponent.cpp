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

#include "AppProperties.h"
#include "ImageEditorComponent.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...

#include "ImageEditorModel.h"

static const double kDefaultWidth = 1030.0;
static const double kDefaultHeight = 490.0;

//[/MiscUserDefs]

//==============================================================================
ImageEditorComponent::ImageEditorComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (redSlider = new Slider ("redSlider"));
    redSlider->setExplicitFocusOrder (1);
    redSlider->setRange (-50, 50, 1);
    redSlider->setSliderStyle (Slider::LinearHorizontal);
    redSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 30, 20);
    redSlider->addListener (this);

    addAndMakeVisible (greenSlider = new Slider ("greenSlider"));
    greenSlider->setExplicitFocusOrder (2);
    greenSlider->setRange (-50, 50, 1);
    greenSlider->setSliderStyle (Slider::LinearHorizontal);
    greenSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 30, 20);
    greenSlider->addListener (this);

    addAndMakeVisible (blueSlider = new Slider ("blueSlider"));
    blueSlider->setExplicitFocusOrder (3);
    blueSlider->setRange (-50, 50, 1);
    blueSlider->setSliderStyle (Slider::LinearHorizontal);
    blueSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 30, 20);
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

    addAndMakeVisible (greenLabel = new Label ("greenLabel",
                                               TRANS("Green")));
    greenLabel->setFont (Font (15.00f, Font::plain));
    greenLabel->setJustificationType (Justification::centredRight);
    greenLabel->setEditable (false, false, false);
    greenLabel->setColour (TextEditor::textColourId, Colours::black);
    greenLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (blueLabel = new Label ("blueLabel",
                                              TRANS("Blue\n")));
    blueLabel->setFont (Font (15.00f, Font::plain));
    blueLabel->setJustificationType (Justification::centredRight);
    blueLabel->setEditable (false, false, false);
    blueLabel->setColour (TextEditor::textColourId, Colours::black);
    blueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (fileLabel = new Label ("fileLabel",
                                              TRANS("Folder:")));
    fileLabel->setFont (Font (15.00f, Font::plain));
    fileLabel->setJustificationType (Justification::centredLeft);
    fileLabel->setEditable (false, false, false);
    fileLabel->setColour (TextEditor::textColourId, Colours::black);
    fileLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (fileSelector = new Slider ("fileSelector"));
    fileSelector->setRange (0, 0, 1);
    fileSelector->setSliderStyle (Slider::IncDecButtons);
    fileSelector->setTextBoxStyle (Slider::TextBoxLeft, true, 80, 20);
    fileSelector->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1030, 490);


    //[Constructor] You can add your own custom stuff here..

    redSlider->setValue(AppProperties::getInstance()->getIntValue("redValue"));
    greenSlider->setValue(AppProperties::getInstance()->getIntValue("greenValue"));
    blueSlider->setValue(AppProperties::getInstance()->getIntValue("blueValue"));

//    beforeImageView->setImage(ImageCache::getFromMemory(BinaryData::RedWeasel_jpeg, BinaryData::RedWeasel_jpegSize));
    afterImageView->setImage(adjustRGB());

    ImageEditorModel::getInstance()->beforeImageFullPathName.addListener(this);

    fileSelector->setEnabled(false);
    fileSelector->setWantsKeyboardFocus(false);
    fileSelector->setLookAndFeel(&fileSelectorLookAndFeel); // disables keyboard focus on the inc/dec buttons

    //[/Constructor]
}

ImageEditorComponent::~ImageEditorComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    AppProperties::getInstance()->setValue("redValue", redSlider->getValue());
    AppProperties::getInstance()->setValue("greenValue", greenSlider->getValue());
    AppProperties::getInstance()->setValue("blueValue", blueSlider->getValue());
    //[/Destructor_pre]

    redSlider = nullptr;
    greenSlider = nullptr;
    blueSlider = nullptr;
    beforeImageView = nullptr;
    afterImageView = nullptr;
    redLabel = nullptr;
    greenLabel = nullptr;
    blueLabel = nullptr;
    fileLabel = nullptr;
    fileSelector = nullptr;


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
    greenSlider->setBounds (568, 368, 450, 24);
    blueSlider->setBounds (568, 409, 450, 24);
    beforeImageView->setBounds (8, 12, 500, 300);
    afterImageView->setBounds (520, 12, 500, 300);
    redLabel->setBounds (522, 330, 38, 24);
    greenLabel->setBounds (505, 368, 54, 24);
    blueLabel->setBounds (521, 408, 38, 24);
    fileLabel->setBounds (13, 328, 491, 24);
    fileSelector->setBounds (20, 360, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    shiftXYPositionForComponent(redSlider);
    shiftXYPositionForComponent(greenSlider);
    shiftXYPositionForComponent(blueSlider);
    shiftXYPositionForComponent(redLabel);
    shiftXYPositionForComponent(greenLabel);
    shiftXYPositionForComponent(blueLabel);
    shiftYPositionForComponent(fileLabel);
    shiftYPositionForComponent(fileSelector);
    const double kWidthScale = (double)getWidth()/kDefaultWidth;
    fileLabel->setBounds(fileLabel->getX(), fileLabel->getY(), fileLabel->getWidth()*kWidthScale, fileLabel->getHeight());
    const int bottom = redSlider->getY() - 30;
    beforeImageView->setBounds (8, 12, 500*kWidthScale, bottom);
    afterImageView->setBounds (520*kWidthScale, 12, 500*kWidthScale, bottom);
    //[/UserResized]
}

void ImageEditorComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == redSlider)
    {
        //[UserSliderCode_redSlider] -- add your slider handling code here..
        afterImageView->setImage(adjustRGB());
        //[/UserSliderCode_redSlider]
    }
    else if (sliderThatWasMoved == greenSlider)
    {
        //[UserSliderCode_greenSlider] -- add your slider handling code here..
        afterImageView->setImage(adjustRGB());
        //[/UserSliderCode_greenSlider]
    }
    else if (sliderThatWasMoved == blueSlider)
    {
        //[UserSliderCode_blueSlider] -- add your slider handling code here..
        afterImageView->setImage(adjustRGB());
        //[/UserSliderCode_blueSlider]
    }
    else if (sliderThatWasMoved == fileSelector)
    {
        //[UserSliderCode_fileSelector] -- add your slider handling code here..
        inputFileIndex = fileSelector->getValue() - 1;
        const File file = inputFiles[inputFileIndex];
        ImageEditorModel::getInstance()->beforeImageFullPathName = file.getFullPathName();
        //[/UserSliderCode_fileSelector]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

bool ImageEditorComponent::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    if( key.isKeyCode(KeyPress::leftKey) )
    {
        if( inputFiles.size() && inputFileIndex > 0 )
        {
            fileSelector->setValue(fileSelector->getValue()-1);
            return true;
        }
    }
    else if( key.isKeyCode(KeyPress::rightKey) )
    {
        if( inputFiles.size() && inputFileIndex < inputFiles.size() - 1 )
        {
            fileSelector->setValue(fileSelector->getValue()+1);
            return true;
        }
    }
    else if( key.getTextCharacter() == 's' )
    {
        if( inputFiles.size() )
        {
            const File& f = ImageEditorModel::getInstance()->formSaveFileFullPathName();
            saveImageFile(f);
            return true;
        }
    }

    return false;
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

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

#if 0
#pragma mark our stuff
#endif

static uint8 adjust(uint8 color, double percent)
{
    const int result = color + 255 * percent;

    return std::max(std::min(result,255),0);
}

Image
ImageEditorComponent::adjustRGB(bool rescale)
{
    Image image = beforeImageView->getImage();
    const bool haveImage = image.isValid();

    redSlider->setEnabled(haveImage);
    greenSlider->setEnabled(haveImage);
    blueSlider->setEnabled(haveImage);

    if( !haveImage ) {
        return Image::null;
    }

    // values are from -50 to 50 with 0 being normal
    // 0 results in no change
    // -50 results in -50%
    // +50 results in +50%
    const double redPercent = redSlider->getValue()/100.0;
    const double greenPercent = greenSlider->getValue()/100.0;
    const double bluePercent = blueSlider->getValue()/100.0;

    if( rescale )
    {
        const double srcWidth = image.getWidth();
        const double srcHeight = image.getHeight();
        const double dstWidth = afterImageView->getWidth();
        const double dstHeight = afterImageView->getHeight();
        if( srcWidth > dstWidth || srcHeight > dstHeight )
        {
            // downscale the destination image will preserving the aspect ratio
            const double hScale = srcWidth / dstWidth;
            const double vScale = srcHeight / dstHeight;
            const double scale = std::max(hScale,vScale);
            image = image.rescaled(srcWidth/scale, srcHeight/scale, Graphics::highResamplingQuality);
        }
    }
    image.duplicateIfShared();

    for( int x=0; x<image.getWidth(); ++x ) {
        for( int y=0; y<image.getHeight(); ++y )
        {
            const Colour pixel(image.getPixelAt(x, y));
            image.setPixelAt(x, y, Colour(adjust(pixel.getRed(), redPercent),
                                          adjust(pixel.getGreen(), greenPercent),
                                          adjust(pixel.getBlue(), bluePercent),
                                          pixel.getAlpha()));
        }
    }

    return image;
}

void
ImageEditorComponent::loadImageFile(const File& file)
{
    const File folder = file.getParentDirectory();
    const bool newFolder = !inputFiles.size()|| inputFiles[0].getParentDirectory() != folder;
    if( newFolder )
    {
        inputFiles.clear();
        int count = folder.findChildFiles(inputFiles, File::findFiles+File::ignoreHiddenFiles, false, kImageWildcardPattern);
        inputFileIndex = -1;
        for( int i=count-1; i>=0; --i )
        {
            const File& f = inputFiles[i];
            if( f == file ) {
                inputFileIndex = i;
            } else if( f.getFullPathName().contains(kOutputImageSuffix) ) {
                inputFiles.remove(i);
            }
        }
        count = inputFiles.size();
        fileSelector->setRange(1,count,1);
        fileSelector->setValue(inputFileIndex+1);
        fileSelector->setTextValueSuffix(String::formatted(" of %d",count));
        fileSelector->setEnabled(count>0);
    }

    beforeImageView->setImage(ImageFileFormat::loadFrom(file));
    afterImageView->setImage(adjustRGB());

    fileLabel->setText("File: " + file.getFullPathName(), dontSendNotification);
    
    grabKeyboardFocus(); // enables our shortcut keys
}

void
ImageEditorComponent::saveImageFile(const File& file)
{
   ImageEditorModel::getInstance()->saveImageFile(file, adjustRGB(false));
}

void ImageEditorComponent::shiftXYPositionForComponent(Component* c)
{
    c->setBounds (
        getWidth()-(kDefaultWidth-c->getX()),
        getHeight()-(kDefaultHeight-c->getY()-c->getHeight()),
        c->getWidth(),
        c->getHeight());
}

void ImageEditorComponent::shiftYPositionForComponent(Component* c)
{
    c->setBounds (
        c->getX(),
        getHeight()-(kDefaultHeight-c->getY()-c->getHeight()),
        c->getWidth(),
        c->getHeight());
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
  <METHODS>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="redSlider" id="bdb7303b5032438b" memberName="redSlider"
          virtualName="" explicitFocusOrder="1" pos="568 329 450 24" min="-50"
          max="50" int="1" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="greenSlider" id="436a5ff4bb288b22" memberName="greenSlider"
          virtualName="" explicitFocusOrder="2" pos="568 368 450 24" min="-50"
          max="50" int="1" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="blueSlider" id="98f2f7171ee398f0" memberName="blueSlider"
          virtualName="" explicitFocusOrder="3" pos="568 409 450 24" min="-50"
          max="50" int="1" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="20" skewFactor="1"
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
  <LABEL name="greenLabel" id="fff9a69e7f26bb1f" memberName="greenLabel"
         virtualName="" explicitFocusOrder="0" pos="505 368 54 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Green" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <LABEL name="blueLabel" id="9f5edce0b62335fe" memberName="blueLabel"
         virtualName="" explicitFocusOrder="0" pos="521 408 38 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Blue&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <LABEL name="fileLabel" id="aa31e0817222723f" memberName="fileLabel"
         virtualName="" explicitFocusOrder="0" pos="13 328 491 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Folder:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="fileSelector" id="a5652d32a507595a" memberName="fileSelector"
          virtualName="" explicitFocusOrder="0" pos="20 360 150 24" min="0"
          max="0" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
