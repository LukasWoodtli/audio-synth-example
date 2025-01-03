//
// Created by Lukas Woodtli on 23.04.2024.
//

#include "FilterComponent.h"

FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId)
{
    juce::StringArray choices {"Low-Pass", "Band-Pass", "High-Pass"};
    filterTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(filterTypeSelector);

    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterTypeSelectorId, filterTypeSelector);


    setSliderWithLabel(filterFreqSlider, filterFreqLabel, apvts, filterFreqId, filterFreqAttachment);
    setSliderWithLabel(filterResSlider, filterResLabel, apvts, filterResId, filterResAttachment);
}

void FilterComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void FilterComponent::resized()
{
    const auto sliderPosY = 80;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;



    filterTypeSelector.setBounds(0, 0, 90, 20);

    filterFreqSlider.setBounds(0, sliderPosY, sliderWidth, sliderHeight);
    filterFreqLabel.setBounds(
        filterFreqSlider.getX(),
        filterFreqSlider.getY() - labelYOffset,
        filterFreqSlider.getWidth(),
        labelHeight);

    filterResSlider.setBounds(filterFreqSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
    filterResLabel.setBounds(
        filterResSlider.getX(),
        filterResSlider.getY() - labelYOffset,
        filterResSlider.getWidth(),
        labelHeight);
}

void FilterComponent::setSliderWithLabel(juce::Slider& slider,
    juce::Label& label,
    juce::AudioProcessorValueTreeState& apvts,
    juce::String paramId,
    SliderAttachment& attachment) {

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}