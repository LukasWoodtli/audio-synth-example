#ifndef PLUGINEXAMPLE_OSCCOMPONENT_H
#define PLUGINEXAMPLE_OSCCOMPONENT_H

#include "juce_gui_basics/juce_gui_basics.h"
#include <juce_audio_processors/juce_audio_processors.h>

class OscComponent : public juce::Component
{
public:
    explicit OscComponent(juce::AudioProcessorValueTreeState &apvts,
        juce::String waveSelectorID,
        juce::String fmFreqId,
        juce::String fmDepthId);
    ~OscComponent() override;

public:
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;

    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;

    using SliderAttachment = std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>;
    SliderAttachment fmFreqAttachment;
    SliderAttachment fmDepthAttachment;

    juce::Label fmFreqLabel { "FM Freq", "FM Freq" };
    juce::Label fmDepthLabel { "FM Depth", "FM Depth" };

    void setSliderWithLabel(juce::Slider& slider,
        juce::Label& label,
        juce::AudioProcessorValueTreeState& apvts,
        juce::String paramId,
        SliderAttachment& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscComponent)
};

#endif //PLUGINEXAMPLE_OSCCOMPONENT_H
