#include <memory>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"
#include "SynthSound.h"

//==============================================================================
PluginProcessor::PluginProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
      apvts(*this, nullptr, "Parameters", createParams())
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

PluginProcessor::~PluginProcessor()
{

}

//==============================================================================
const juce::String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginProcessor::getCurrentProgram()
{
    return 0;
}

void PluginProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String PluginProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void PluginProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (auto i = 0; i < synth.getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }

    filter.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
}

void PluginProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void PluginProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (auto i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))){
            // ADSR
            const auto& attack = *apvts.getRawParameterValue("ATTACK");
            const auto& decay = *apvts.getRawParameterValue("DECAY");
            const auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            const auto& release = *apvts.getRawParameterValue("RELEASE");
            voice->updateADSR(attack.load(), decay.load(), sustain.load(), release.load());

            // OSC control
            auto& oscWaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");
            voice->getOscillator().setWaveType((const int)oscWaveChoice);

            const auto& fmDepth = *apvts.getRawParameterValue("OSC1FMDEPTH");
            const auto& fmFreq = *apvts.getRawParameterValue("OSC1FMFREQ");
            voice->getOscillator().setFmParams(fmDepth, fmFreq);

            // LFO
        }
    }

/*    for (const juce::MidiMessageMetadata metadata : midiMessages)
        if (metadata.numBytes == 3)
            juce::Logger::writeToLog ("MIDI: " + juce::String(metadata.getMessage().getTimeStamp())
                + " - " + metadata.getMessage().getDescription());
*/
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    // Filter
    const auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
    const auto& filterCutoff = *apvts.getRawParameterValue("FILTERCUTOFF");
    const auto& filterResonance = *apvts.getRawParameterValue("FILTERRES");
    filter.updateParameters((int)filterType.load(), filterCutoff.load(), filterResonance.load());

    filter.process(buffer);
}

//==============================================================================
bool PluginProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (*this);
}

//==============================================================================
void PluginProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Osc Combobox: switch oscillator shape
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{"OSC1WAVETYPE", 1}, "Oscillator 1 Wave Type",
        juce::StringArray { "Sine", "Saw", "Square"}, 0));

    // FM
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"OSC1FMFREQ", 1}, "FM Oscillator 1 Frequency", juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"OSC1FMDEPTH", 1}, "FM Oscillator 1 Depth", juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f}, 0.0f));

    // ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"ATTACK", 1}, "Attack", juce::NormalisableRange<float> {0.1f, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"DECAY", 1}, "Decay", juce::NormalisableRange<float> {0.1f, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"SUSTAIN", 1}, "Sustain", juce::NormalisableRange<float> {0.1f, 1.0f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"RELEASE", 1}, "Release", juce::NormalisableRange<float> {0.1f, 3.0f}, 0.4f));

    // Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{"FILTERTYPE", 1}, "Filter Type",
        juce::StringArray { "Low-Pass", "Band-Pass", "High-Pass"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"FILTERCUTOFF", 1}, "Filter Cutoff", juce::NormalisableRange<float> {20.0f, 20000.0f, 0.1f, 0.6f}, 200.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"FILTERRES", 1}, "Filter Resonance", juce::NormalisableRange<float> {1.0f, 10.0f, 0.1f }, 1.0f));


    return { params.begin(), params.end() };
}
