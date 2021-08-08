#pragma once

#include <JuceHeader.h>
#include "NumberBox.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    NumberBox blueBox, greenBox, yellowBox;
    
    juce::Colour blue   = juce::Colour::fromFloatRGBA (0.43f, 0.83f, 1.0f,  1.0f);
    juce::Colour green  = juce::Colour::fromFloatRGBA (0.34f, 0.74f, 0.66f, 1.0f);
    juce::Colour yellow = juce::Colour::fromFloatRGBA (1.0f,  0.71f, 0.2f,  1.0f);
    juce::Colour black  = juce::Colour::fromFloatRGBA (0.08f, 0.08f, 0.08f, 1.0f);


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
