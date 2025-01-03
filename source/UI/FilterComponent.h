//
// Created by Lukas Woodtli on 23.04.2024.
//

#ifndef PLUGINEXAMPLE_FILTERCOMPONENT_H
#define PLUGINEXAMPLE_FILTERCOMPONENT_H

#include "juce_gui_basics/juce_gui_basics.h"
#include <juce_audio_processors/juce_audio_processors.h>

class FilterComponent : public juce::Component
{
public:
    explicit FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId);
    virtual ~FilterComponent() override {}

    void paint(juce::Graphics& g) override;
    void resized() override;
private:
    juce::ComboBox filterTypeSelector{ "Filter Type" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;

    juce::Slider filterFreqSlider;
    juce::Slider filterResSlider;

    using SliderAttachment = std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>;
    SliderAttachment filterFreqAttachment;
    SliderAttachment filterResAttachment;

    juce::Label filterSelectorLabel { "Filter Type", "Filter Type" };
    juce::Label filterFreqLabel { "Filter Freq", "Filter Freq" };
    juce::Label filterResLabel { "Filter Res", "Filter Res" };


    void setSliderWithLabel(juce::Slider& slider,
        juce::Label& label,
        juce::AudioProcessorValueTreeState& apvts,
        juce::String paramId,
        SliderAttachment& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterComponent)
};

#endif //PLUGINEXAMPLE_FILTERCOMPONENT_H
