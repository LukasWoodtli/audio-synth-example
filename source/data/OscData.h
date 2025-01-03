//
// Created by Lukas Woodtli on 10.04.2024.
//

#ifndef PLUGINEXAMPLE_OSCDATA_H
#define PLUGINEXAMPLE_OSCDATA_H

#include <juce_dsp/juce_dsp.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType (const int choice);
    void setWaveFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setFmParams(const float depth, const float frequency);

private:
    juce::dsp::Oscillator<float> fmOsc{ [](float x) { return std::sin(x); } };
    float fmMod = 0.0f;
    float fmDepth = 0.0f;
    int lastMidiNote = 0;
};

#endif //PLUGINEXAMPLE_OSCDATA_H
