/*
  ==============================================================================

    NumberBox.h
    Created: 8 Aug 2021 7:46:08am
    Author:  Kengo Suzuki

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CustomLabel : public juce::Label
{
public:
    static juce::String initialPressedKey;

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
class NumberBox  : public juce::Slider, public juce::KeyListener
{
public:
    NumberBox();    
    
    void paint (juce::Graphics& g) override;
    void mouseDown (const juce::MouseEvent& event) override;
    void mouseUp (const juce::MouseEvent& event) override;
    bool keyPressed (const juce::KeyPress& k, juce::Component* c) override;
    
private:
    CustomLookAndFeel customLookAndFeel;
    
    juce::Colour grey = juce::Colour::fromFloatRGBA (0.42f, 0.42f, 0.42f, 1.f);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NumberBox)
};