//
// Created by Lukas Woodtli on 20.03.2024.
//

#include "SynthVoice.h"
#include "SynthSound.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}


void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();

    if (!allowTailOff || !adsr.isActive()) {
        clearCurrentNote();
    }
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{

}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels)
{

    synthBuffer.setSize(numOutputChannels, samplesPerBlock);
    synthBuffer.clear();

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = (uint32_t)samplesPerBlock;
    spec.numChannels = (uint32_t)numOutputChannels;

    osc.prepareToPlay(spec);
    gain.prepare(spec);

    gain.setGainLinear(0.3f);

    adsr.setSampleRate(sampleRate);

    isPrepared = true;
}

void SynthVoice::updateADSR (const float attack, const float decay, const float sustain, const float release) {
    adsr.update (attack, decay, sustain, release);
}

void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    if (!isVoiceActive()) {
        return;
    }
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);

    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    osc.getNextAudioBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (!adsr.isActive()) {
            clearCurrentNote();
        }
    }
}
