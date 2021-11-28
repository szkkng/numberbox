/*
  ==============================================================================

    NumberBox.h
    Created: 8 Aug 2021 7:46:08am
    Author:  Kengo Suzuki

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Resources/FuturaMedium.h"

class CustomLabel : public juce::Label
{
public:
    static juce::String initialValue;

    juce::TextEditor* createEditorComponent() override;
    void editorShown (juce::TextEditor* editor) override;
};

//==============================================================================
class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel();
    
    juce::CaretComponent* createCaretComponent (juce::Component* keyFocusOwner) override;
    CustomLabel* createSliderTextBox (juce::Slider& slider) override;
};

//==============================================================================
class NumberBox  : public juce::Slider
{
public:
    NumberBox();
    ~NumberBox();
    
    void paint (juce::Graphics& g) override;
    void mouseDown (const juce::MouseEvent& event) override;
    void mouseUp (const juce::MouseEvent& event) override;
    bool keyPressed (const juce::KeyPress& k) override;
    
private:
    void drawFocusMark (juce::Graphics& g, juce::Colour colour);
    
    CustomLookAndFeel customLookAndFeel;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NumberBox)
};
