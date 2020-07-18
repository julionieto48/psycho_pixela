/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Psyco_pseudoPixelaFiltersPlugInAudioProcessorEditor::Psyco_pseudoPixelaFiltersPlugInAudioProcessorEditor (Psyco_pseudoPixelaFiltersPlugInAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    // ToggleButton de ByPass
    bypassTogglebutton.setButtonText("ByPass");
    bypassTogglebutton.onStateChange = [this] {processor.buttonState = bypassTogglebutton.getToggleState();};
    addAndMakeVisible(&bypassTogglebutton);
    
    
    // Label de PiscoPixela
    PsicoPixelaLabel.setText("Psyco/Pseudo-Pixela", dontSendNotification);
    PsicoPixelaLabel.setFont(Font(25.f, Font::bold));
    addAndMakeVisible(&PsicoPixelaLabel);
    
    // Label de titulo
    titleLabel.setText("PQMF & IPQMF Process", dontSendNotification);
    titleLabel.setFont(Font(20.f, Font::bold));
    addAndMakeVisible(&titleLabel);
    
    _125.setText("125", dontSendNotification);_125.setFont(Font(11.f, Font::bold));addAndMakeVisible(&_125);
    _250.setText("250", dontSendNotification);_250.setFont(Font(11.f, Font::bold));addAndMakeVisible(&_250);
    _500.setText("500", dontSendNotification);_500.setFont(Font(11.f, Font::bold));addAndMakeVisible(&_500);
    _1000.setText("1000", dontSendNotification);_1000.setFont(Font(11.f, Font::bold));addAndMakeVisible(&_1000);
    _2000.setText("2000", dontSendNotification);_2000.setFont(Font(11.f, Font::bold));addAndMakeVisible(&_2000);
    _4000.setText("4000", dontSendNotification);_4000.setFont(Font(11.f, Font::bold));addAndMakeVisible(&_4000);
    _8000.setText("8000", dontSendNotification);_8000.setFont(Font(11.f, Font::bold));addAndMakeVisible(&_8000);
    _Hz.setText("Hz", dontSendNotification);_Hz.setFont(Font(12.f, Font::bold));addAndMakeVisible(&_Hz);
    
    
    setSize (800, 600);
    startTimerHz (30);
}

Psyco_pseudoPixelaFiltersPlugInAudioProcessorEditor::~Psyco_pseudoPixelaFiltersPlugInAudioProcessorEditor()
{
    
}

void Psyco_pseudoPixelaFiltersPlugInAudioProcessorEditor::timerCallback(){
    if (processor.nextFFTBlockReady){
        processor.drawNextFrameOfSpectrum();
        processor.nextFFTBlockReady = false;
        repaint();
    }
}
//==============================================================================
void Psyco_pseudoPixelaFiltersPlugInAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
    
    auto width  = getLocalBounds().getWidth()-100;
    auto height = getLocalBounds().getHeight();
    
    //g.fillAll (Colours::blanchedalmond);
    g.fillAll (Colours::black);
    g.setOpacity(1.0f); g.setColour (Colours::white);
    drawFrame(g);
    
    auto min_pos = 0.27f;
    auto max_pos = 0.3f;
    int scopeSize = 512;
    
    g.drawLine ({
        (float) jmap (0, 0, scopeSize , 100, width),
        jmap (0.285f,0.0f, 1.0f, (float) height, 0.0f),
        (float) jmap (512, 0, scopeSize , 100, width),
        jmap (0.285f,0.0f, 1.0f, (float) height, 0.0f) });
    
    g.drawLine ({
        (float) jmap (0, 0, scopeSize , 100, width),
        jmap (0.285f,0.0f, 1.0f, (float) height, 0.0f),
        (float) jmap (0, 0, scopeSize , 100, width),
        jmap (0.9f,0.0f, 1.0f, (float) height, 0.0f) });
    
    int f = 15; //125 Hz
    g.drawLine ({ (float) jmap (f, 0, scopeSize , 100, width),
        jmap (min_pos, 0.0f, 1.0f, (float) height, 0.0f),
        (float) jmap (f,0, scopeSize , 100, width),
        jmap (max_pos,0.0f, 1.0f, (float) height, 0.0f) });
    f = 30; //250 Hz
    g.drawLine ({ (float) jmap (f, 0, scopeSize , 100, width),
        jmap (min_pos, 0.0f, 1.0f, (float) height, 0.0f),
        (float) jmap (f,0, scopeSize, 100, width),
        jmap (max_pos,0.0f, 1.0f, (float) height, 0.0f) });
    f = 56; //500 Hz
    g.drawLine ({ (float) jmap (f, 0, scopeSize , 100, width),
        jmap (min_pos, 0.0f, 1.0f, (float) height, 0.0f),
        (float) jmap (f,0, scopeSize , 100, width),
        jmap (max_pos,0.0f, 1.0f, (float) height, 0.0f) });
    f = 108; //1k Hz
    g.drawLine ({ (float) jmap (f, 0, scopeSize , 100, width),
        jmap (min_pos, 0.0f, 1.0f, (float) height, 0.0f),
        (float) jmap (f,0, scopeSize , 100, width),
        jmap (max_pos,0.0f, 1.0f, (float) height, 0.0f) });
    f = 195;  //2k Hz
    g.drawLine ({ (float) jmap (f, 0, scopeSize , 100, width),
        jmap (min_pos, 0.0f, 1.0f, (float) height, 0.0f),
        (float) jmap (f,0, scopeSize , 100, width),
        jmap (max_pos,0.0f, 1.0f, (float) height, 0.0f) });
    f = 326; //4k Hz
    g.drawLine ({ (float) jmap (f, 0, scopeSize , 100, width),
        jmap (min_pos, 0.0f, 1.0f, (float) height, 0.0f),
        (float) jmap (f,0, scopeSize , 100, width),
        jmap (max_pos,0.0f, 1.0f, (float) height, 0.0f) });
    f = 459; //8k Hz
    g.drawLine ({ (float) jmap (f, 0, scopeSize , 100, width),
        jmap (min_pos, 0.0f, 1.0f, (float) height, 0.0f),
        (float) jmap (f,0, scopeSize , 100, width),
        jmap (max_pos,0.0f, 1.0f, (float) height, 0.0f) });
    
}

void Psyco_pseudoPixelaFiltersPlugInAudioProcessorEditor::drawFrame (Graphics& g){
    
    int scopeSizer = processor.scopeSize;
    float *scopeDatar = processor.scopeData;
    for (int i = 1; i < scopeSizer; ++i){
        auto width  = getLocalBounds().getWidth() - 100;
        auto height = getLocalBounds().getHeight();
        
        g.drawLine ({ (float) jmap (i - 1, 0, scopeSizer - 1, 100, width),
            jmap (scopeDatar[i - 1], -0.4f, 1.0f, (float) height, 0.0f),
            (float) jmap (i,     0, scopeSizer - 1, 100, width),
            jmap (scopeDatar[i],     -0.4f, 1.0f, (float) height, 0.0f) });
    }
}

void Psyco_pseudoPixelaFiltersPlugInAudioProcessorEditor::resized()
{
    // ToggleButtons
    bypassTogglebutton.setBounds(getWidth() *0.77, 200+getHeight()/2, 80, 40);
    
    // Labels
    PsicoPixelaLabel.setBounds(400, 10, getWidth() - 100, 40);
    titleLabel.setBounds(10, 10, getWidth() - 100, 40);
    
    auto width  = getLocalBounds().getWidth()-100;
    auto height = getLocalBounds().getHeight();
    int scopeSize = 512; int factoy = 10;
    int f = 6;
    _125.setBounds((float) jmap (f, 0, scopeSize , 100, width), jmap (0.27f, 0.0f, 1.0f, (float) height, 0.0f)-factoy, 80, 40);
    f = 25;
    _250.setBounds((float) jmap (f, 0, scopeSize , 100, width), jmap (0.27f, 0.0f, 1.0f, (float) height, 0.0f)-factoy, 80, 40);
    f = 49;
    _500.setBounds((float) jmap (f, 0, scopeSize , 100, width), jmap (0.27f, 0.0f, 1.0f, (float) height, 0.0f)-factoy, 80, 40);
    f = 100;
    _1000.setBounds((float) jmap (f, 0, scopeSize , 100, width), jmap (0.27f, 0.0f, 1.0f, (float) height, 0.0f)-factoy, 80, 40);
    f = 187;
    _2000.setBounds((float) jmap (f, 0, scopeSize , 100, width), jmap (0.27f, 0.0f, 1.0f, (float) height, 0.0f)-factoy, 80, 40);
    f = 320;
    _4000.setBounds((float) jmap (f, 0, scopeSize , 100, width), jmap (0.27f, 0.0f, 1.0f, (float) height, 0.0f)-factoy, 80, 40);
    f = 453;
    _8000.setBounds((float) jmap (f, 0, scopeSize , 100, width), jmap (0.27f, 0.0f, 1.0f, (float) height, 0.0f)-factoy, 80, 40);
    f = 512;
    _Hz.setBounds((float) jmap (f, 0, scopeSize , 100, width), jmap (0.27f, 0.0f, 1.0f, (float) height, 0.0f)-factoy, 80, 40);
    
}
