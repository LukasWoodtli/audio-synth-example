//
// Created by Lukas Woodtli on 01.04.2024.
//

#ifndef PLUGINEXAMPLE_ADSRDATA_H
#define PLUGINEXAMPLE_ADSRDATA_H

#include <juce_audio_processors/juce_audio_processors.h>


class AdsrData : public juce::ADSR
{

public:
    void update (const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParams;
};

#endif //PLUGINEXAMPLE_ADSRDATA_H
