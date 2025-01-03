
#ifndef PLUGINEXAMPLE_SYNTHSOUND_H
#define PLUGINEXAMPLE_SYNTHSOUND_H

#include <juce_audio_basics/juce_audio_basics.h>

class SynthSound : public juce::SynthesiserSound {
    bool appliesToNote (int /*midiNoteNumber*/) override { return true; }
    bool appliesToChannel (int /*midiChannel*/) override { return true; }

};
#endif //PLUGINEXAMPLE_SYNTHSOUND_H
