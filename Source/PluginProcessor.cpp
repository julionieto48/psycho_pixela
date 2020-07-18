/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Psyco_pseudoPixelaFiltersPlugInAudioProcessor::Psyco_pseudoPixelaFiltersPlugInAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
:
                    AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
forwardFFT (fftOrder)
#endif

{
    output_sintesis = NULL;
    //recons_signal = NULL;
}

Psyco_pseudoPixelaFiltersPlugInAudioProcessor::~Psyco_pseudoPixelaFiltersPlugInAudioProcessor()
{
    if (output_sintesis) {delete [] output_sintesis;}
    //if (recons_signal) {delete [] recons_signal;}
    x.~CircularPQMF_Buffer();
    PQMF_processor.~PQMF_Analysis();
    IPQMF_processor.~IPQMF_Synthesis();
}

//==============================================================================
const String Psyco_pseudoPixelaFiltersPlugInAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Psyco_pseudoPixelaFiltersPlugInAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Psyco_pseudoPixelaFiltersPlugInAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Psyco_pseudoPixelaFiltersPlugInAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Psyco_pseudoPixelaFiltersPlugInAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Psyco_pseudoPixelaFiltersPlugInAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Psyco_pseudoPixelaFiltersPlugInAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Psyco_pseudoPixelaFiltersPlugInAudioProcessor::setCurrentProgram (int index)
{
}

const String Psyco_pseudoPixelaFiltersPlugInAudioProcessor::getProgramName (int index)
{
    return {};
}

void Psyco_pseudoPixelaFiltersPlugInAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Psyco_pseudoPixelaFiltersPlugInAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    x.setBufferSize(512);
    nextFFTBlockReady = false;
    if (output_sintesis) {delete [] output_sintesis;}
    //if (recons_signal) {delete [] recons_signal;}

    output_sintesis = new float[32];
    
}

void Psyco_pseudoPixelaFiltersPlugInAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Psyco_pseudoPixelaFiltersPlugInAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Psyco_pseudoPixelaFiltersPlugInAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    //recons_signal = new float[buffer.getNumSamples()];

    if (buttonState == false) {
        float recons_signal[buffer.getNumSamples()];
        
        //Set del numero de bloques de a 32 a procesar:
        for(int blockIndex = 0; blockIndex < buffer.getNumSamples()/32; blockIndex++){
            //Indexación de a 32 muestras en el buffer circular.
            for (int i = 0; i < 32; i++)
                x.addSample(buffer.getSample(0, i + blockIndex*32));
            
            //Procesamiento del buffer circular con el PQMF y el IPQMF.
            output_sintesis = IPQMF_processor.IPQMF_Filtering(PQMF_processor.PQMF_Filtering(x.buffer));
            
            //Indexación de la señal reconstruida de a bloques de 32 hasta llenarse a bufferToFill.numSamples
            for(int n = 0; n < 32; n++)
                recons_signal[n + blockIndex*32] = *(output_sintesis + n);
        }
        
        //Corrección por promediación de las últimas muestras de cada sálida y[32] de síntesis:
        for (int i = 31; i < buffer.getNumSamples(); i+=32){
            if (i == buffer.getNumSamples() - 1){
                recons_signal[i] = recons_signal[i-1];
                break;
            }else{
                recons_signal[i] = 0.5*(recons_signal[i-1] + recons_signal[i+1]);
            }
        }
        
        //Indexación de la señal reconstruida en el buffer de salida:
        for (int channel = 0; channel < totalNumInputChannels; ++channel){
            auto* channelData = buffer.getWritePointer (channel);
            for (auto n = 0; n < buffer.getNumSamples(); n++){
                channelData[n] = recons_signal[n];
                pushNextSampleIntoFifo(recons_signal[n]);
            }
        }
    }
    else{
        for (int channel = 0; channel < totalNumInputChannels; ++channel){
            auto* channelData = buffer.getWritePointer (channel);
            for (auto n = 0; n < buffer.getNumSamples(); n++){
                pushNextSampleIntoFifo(channelData[n]);
            }
        }
            //por defecto: buffer[n] = audioData[n];
    }
    //delete [] recons_signal;
    

}
//=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.


void Psyco_pseudoPixelaFiltersPlugInAudioProcessor::pushNextSampleIntoFifo (float sample) noexcept{
    // if the fifo contains enough data, set a flag to say
    // that the next frame should now be rendered..
    if (fifoIndex == fftSize){
        if (! nextFFTBlockReady){
            zeromem (fftData, sizeof (fftData));
            memcpy (fftData, fifo, sizeof (fifo));
            nextFFTBlockReady = true;
        }
        fifoIndex = 0;
    }
    fifo[fifoIndex++] = sample;
}

void Psyco_pseudoPixelaFiltersPlugInAudioProcessor::drawNextFrameOfSpectrum(){
    // first apply a windowing function to our data
    window->multiplyWithWindowingTable (fftData, fftSize);
    
    // then render our FFT data..
    forwardFFT.performFrequencyOnlyForwardTransform (fftData);
    
    auto mindB = -100.0f;
    auto maxdB =    0.0f;
    
    for (int i = 0; i < scopeSize; ++i){
        auto skewedProportionX = 1.0f - std::exp (std::log (1.0f - i / (float) scopeSize) * 0.2f);
        auto fftDataIndex = jlimit (0, fftSize / 2, (int) (skewedProportionX * fftSize / 2));
        //std::cout << ((int) (skewedProportionX * fftSize/2)) << std::endl;
        auto level = jmap (jlimit (mindB, maxdB, Decibels::gainToDecibels (fftData[fftDataIndex])
                                   - Decibels::gainToDecibels ((float) fftSize)),
                           mindB, maxdB, 0.0f, 1.0f);
        scopeData[i] = level;
    }
}




//=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.
//==============================================================================
bool Psyco_pseudoPixelaFiltersPlugInAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Psyco_pseudoPixelaFiltersPlugInAudioProcessor::createEditor()
{
    return new Psyco_pseudoPixelaFiltersPlugInAudioProcessorEditor (*this);
}

//==============================================================================
void Psyco_pseudoPixelaFiltersPlugInAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Psyco_pseudoPixelaFiltersPlugInAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Psyco_pseudoPixelaFiltersPlugInAudioProcessor();
}
