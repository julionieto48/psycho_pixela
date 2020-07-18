/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Psyco_pseudoPixelaFiltersPlugInAudioProcessorEditor  : public AudioProcessorEditor, private Timer
{
public:
    Psyco_pseudoPixelaFiltersPlugInAudioProcessorEditor (Psyco_pseudoPixelaFiltersPlugInAudioProcessor&);
    ~Psyco_pseudoPixelaFiltersPlugInAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void drawFrame (Graphics& g);
    void timerCallback() override;
    
    
private:
    
    Psyco_pseudoPixelaFiltersPlugInAudioProcessor& processor;
    
    Label PsicoPixelaLabel;
    Label titleLabel;
    Label _60;Label _125;Label _250;Label _500;Label _1000;Label _2000;Label _4000;Label _8000; Label _Hz;
    
    ToggleButton bypassTogglebutton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Psyco_pseudoPixelaFiltersPlugInAudioProcessorEditor)
};
