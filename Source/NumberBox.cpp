/*
  ==============================================================================

    NumberBox.cpp
    Created: 8 Aug 2021 7:46:08am
    Author:  Kengo Suzuki

  ==============================================================================
*/

#include "NumberBox.h"

juce::String CustomLabel::initialPressedKey = "";

juce::TextEditor* CustomLabel::createEditorComponent()
{
    auto* ed = juce::Label::createEditorComponent();

    ed->setJustification (juce::Justification::centred);
    ed->setColour (juce::TextEditor::backgroundColourId, juce::Colours::transparentWhite);
    ed->setInputRestrictions (5, "0123456789.");
    ed->setIndents (4, 0);

    return ed;
}

void CustomLabel::editorShown (juce::TextEditor* editor)
{
    editor->setMouseCursor (juce::MouseCursor::NoCursor);
    editor->clear();
    editor->setText (initialPressedKey);
}

//==============================================================================
juce::CaretComponent* CustomLookAndFeel::createCaretComponent (juce::Component* keyFocusOwner)
{
    auto caret = new juce::CaretComponent (keyFocusOwner);

    caret->setColour (juce::CaretComponent::caretColourId, keyFocusOwner->findColour (juce::Label::textColourId));

    return caret;
}

CustomLabel* CustomLookAndFeel::createSliderTextBox (juce::Slider& slider)
{
    auto* l = new CustomLabel();
    
    l->setJustificationType (juce::Justification::centred);
    l->setColour (juce::Label::textColourId, slider.findColour (juce::Slider::textBoxTextColourId));
    l->setColour (juce::Label::textWhenEditingColourId, slider.findColour (juce::Slider::textBoxTextColourId));
    l->setColour (juce::Label::outlineWhenEditingColourId, juce::Colours::transparentWhite);
    l->setFont (18);
                
    return l;
}

//==============================================================================
NumberBox::NumberBox()
{
    setLookAndFeel (&customLookAndFeel);
    setColour (juce::Slider::trackColourId, juce::Colours::transparentWhite);
    setSliderStyle (juce::Slider::LinearBarVertical);
    setTextBoxIsEditable (false);
    setVelocityBasedMode (true);
    setVelocityModeParameters (0.8, 1, 0.09, false);
    setRange (0, 100, 0.01);
    setValue (50.0);
    setDoubleClickReturnValue (true, 50.0);
    setTextValueSuffix (" %");
    setWantsKeyboardFocus (true);
    onValueChange = [&]()
    {
        if (getValue() < 10)
            setNumDecimalPlacesToDisplay(2);
        else if (10 <= getValue() && getValue() < 100)
            setNumDecimalPlacesToDisplay(1);
        else
            setNumDecimalPlacesToDisplay(0);
    };
}

NumberBox::~NumberBox()
{
    setLookAndFeel (nullptr);
}

void NumberBox::paint (juce::Graphics& g)
{
    if (hasKeyboardFocus (false))
        drawFocusMark (g, findColour (juce::Slider::textBoxOutlineColourId));
}

void NumberBox::drawFocusMark (juce::Graphics &g, juce::Colour colour)
{
    g.setColour (colour);

    auto bounds = getLocalBounds().toFloat();
    auto length = juce::jmin (bounds.getHeight(), bounds.getWidth()) * 0.15f;
    auto thick  = length * 0.5f;
    auto radian = 0.0f;

    auto topL    = bounds.getTopLeft();
    auto topR    = bounds.getTopRight();
    auto bottomR = bounds.getBottomRight();
    auto bottomL = bounds.getBottomLeft();

    std::array<juce::Point<float>, 4> corners { topL, topR, bottomR, bottomL };

    // Draw in clockwise order, starting from top left.
    for (auto corner : corners)
    {
        juce::Path path;

        // vertical path
        path.startNewSubPath (corner);
        path.lineTo          (corner.x, corner.y + length);

        // horizontal path
        path.startNewSubPath (corner);
        path.lineTo          (corner.x + length, corner.y);

        g.strokePath (path,
                      juce::PathStrokeType (thick),
                      juce::AffineTransform::rotation (radian, corner.x, corner.y));

        radian += juce::MathConstants<float>::halfPi;
    };
}

void NumberBox::mouseDown (const juce::MouseEvent& event)
{
    juce::Slider::mouseDown (event);

    setMouseCursor (juce::MouseCursor::NoCursor);
}

void NumberBox::mouseUp (const juce::MouseEvent& event)
{
    juce::Slider::mouseUp (event);

    juce::Desktop::getInstance().getMainMouseSource().setScreenPosition (event.source.getLastMouseDownPosition());

    setMouseCursor (juce::MouseCursor::NormalCursor);
}

bool NumberBox::keyPressed (const juce::KeyPress& k)
{
    char numChars[] = "0123456789";

    for (auto numChar : numChars)
    {
        if (k.getTextCharacter() == numChar)
        {
            setTextBoxIsEditable (true);
            CustomLabel::initialPressedKey = juce::String::charToString (numChar);
            showTextBox();
            setTextBoxIsEditable (false);

            return true;
        }
    }

    return false;
}
