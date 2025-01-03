//
// Created by Lukas Woodtli on 21.04.2024.
//

#ifndef PLUGINEXAMPLE_FILTERDATA_H
#define PLUGINEXAMPLE_FILTERDATA_H

#include <juce_dsp/juce_dsp.h>

class FilterData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const int parameterType, const float frequency, const float resonance);
    void reset();

private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared = false;
};

#endif //PLUGINEXAMPLE_FILTERDATA_H
