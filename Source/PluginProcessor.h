/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
//#include "PluginEditor.h"

#include "CircularPQMF_Buffer.h"
#include "PQMF_Analysis.h"
#include "IPQMF_Synthesis.h"
//==============================================================================
/**
*/
class Psyco_pseudoPixelaFiltersPlugInAudioProcessor: public AudioProcessor
{
public:
    //==============================================================================
    Psyco_pseudoPixelaFiltersPlugInAudioProcessor();
    ~Psyco_pseudoPixelaFiltersPlugInAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //==============================================================================
    void pushNextSampleIntoFifo (float sample) noexcept;
    void drawNextFrameOfSpectrum();
    
    
    enum{
        fftOrder  = 11,
        fftSize   = 1 << fftOrder,
        scopeSize = 512
    };
    
    float scopeData [scopeSize];
    bool nextFFTBlockReady;
    bool buttonState = false;
    
private:
    
    //float *recons_signal;
    
    CircularPQMF_Buffer x;
    PQMF_Analysis PQMF_processor;
    IPQMF_Synthesis IPQMF_processor;
    
    float * output_sintesis;
    
    //=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=
    //Muestra en Interfáz de análisis espectral
    
    dsp::FFT forwardFFT;
    dsp::WindowingFunction<float>* window = new dsp::WindowingFunction<float>(512, dsp::WindowingFunction<float>::blackmanHarris);
    
    float fifo [fftSize];
    float fftData [2 * fftSize];
    int fifoIndex = 0;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Psyco_pseudoPixelaFiltersPlugInAudioProcessor)
};
