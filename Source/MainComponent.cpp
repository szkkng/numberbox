#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (500, 300);
    setWantsKeyboardFocus (true);
    
    blueBox.setColour (juce::Slider::textBoxTextColourId, blue);
    blueBox.setColour (juce::Slider::textBoxOutlineColourId, blue);
    
    greenBox.setColour (juce::Slider::textBoxTextColourId, green);
    greenBox.setColour (juce::Slider::textBoxOutlineColourId, green);
    
    yellowBox.setColour (juce::Slider::textBoxTextColourId, yellow);
    yellowBox.setColour (juce::Slider::textBoxOutlineColourId, yellow);
    
    addAndMakeVisible (blueBox);
    addAndMakeVisible (greenBox);
    addAndMakeVisible (yellowBox);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (black);
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds().withSizeKeepingCentre (80, 30);
    
    blueBox.setBounds (bounds.withX (50));
    greenBox.setBounds (bounds.withX (205));
    yellowBox.setBounds (bounds.withX (360));
}
