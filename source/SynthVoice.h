
#ifndef PLUGINEXAMPLE_SYNTHVOICE_H
#define PLUGINEXAMPLE_SYNTHVOICE_H
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

#include "data/AdsrData.h"
#include "data/OscData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound*) override;

    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;

    void stopNote (float velocity, bool allowTailOff) override;

    void pitchWheelMoved (int newPitchWheelValue) override;

    void controllerMoved (int controllerNumber, int newControllerValue) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels);

    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;

    void updateADSR(const float attack, const float decay, const float sustain, const float release);

    OscData& getOscillator() { return osc; }
private:
    juce::AudioBuffer<float> synthBuffer;

    OscData osc;
    juce::dsp::Gain<float> gain;
    bool isPrepared = false;

    AdsrData adsr;

};

#endif //PLUGINEXAMPLE_SYNTHVOICE_H
