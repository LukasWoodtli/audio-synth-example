#ifndef PLUGINEXAMPLE_ADSRCOMPONENT_H
#define PLUGINEXAMPLE_ADSRCOMPONENT_H

#include "juce_gui_basics/juce_gui_basics.h"
#include <juce_audio_processors/juce_audio_processors.h>

class AdsrComponent : public juce::Component
{
public:
    AdsrComponent(juce::AudioProcessorValueTreeState& apvts);

    void paint(juce::Graphics& g);
    void resized();
private:
    void setSliderParams(juce::Slider& slider);

private:
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AdsrComponent)
};

#endif //PLUGINEXAMPLE_ADSRCOMPONENT_H
