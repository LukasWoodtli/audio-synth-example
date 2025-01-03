//
// Created by Lukas Woodtli on 21.04.2024.
//

#include "FilterData.h"
#include "juce_audio_plugin_client/detail/juce_IncludeSystemHeaders.h"

void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = (uint32_t)samplesPerBlock;
    spec.numChannels = (uint32_t)numChannels;
    filter.prepare(spec);

    isPrepared = true;
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> audioBlock { buffer };
    filter.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void FilterData::updateParameters(const int parameterType, const float frequency, const float resonance)
{
    filter.setType((juce::dsp::StateVariableTPTFilterType)parameterType);
    filter.setCutoffFrequency(frequency);
    filter.setResonance(resonance);
}

void FilterData::reset()
{
    filter.reset();
}
