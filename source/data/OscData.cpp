//
// Created by Lukas Woodtli on 10.04.2024.
//

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    fmOsc.prepare(spec);
    prepare(spec);
}

void OscData::setWaveType (const int choice)
{
    switch (choice)
    {
        case 0:
            // sine
            initialise([](float x) { return std::sin(x); });
            break;
        case 1:
            // saw
            initialise([](float x) { return x / juce::MathConstants<float>::pi; });
            break;
        case 2:
            // square
            initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; });
            break;
        default:
            jassertfalse;
    }
}


void OscData::setWaveFrequency(const int midiNoteNumber) {
    setFrequency((float)juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
    lastMidiNote = midiNoteNumber;
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    for (auto ch = 0; ch < block.getNumChannels(); ++ch) {
        for (auto s = 0; s < block.getNumSamples(); ++s) {
            fmMod = fmOsc.processSample(block.getSample(ch, s)) * fmDepth;
        }
    }
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::setFmParams(const float depth, const float frequency)
{
    fmDepth = depth;
    fmOsc.setFrequency(frequency);

    const auto currentFreq = (float)juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod;
    setFrequency(std::fabs(currentFreq));
}
