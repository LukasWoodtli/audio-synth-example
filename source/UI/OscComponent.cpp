//
// Created by Lukas Woodtli on 10.04.2024.
//

#include "OscComponent.h"

OscComponent::OscComponent(juce::AudioProcessorValueTreeState &apvts,
    juce::String waveSelectorID,
    juce::String fmFreqId,
    juce::String fmDepthId) {
    juce::StringArray choices {"Sine", "Saw", "Square"};
    oscWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveSelector);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorID, oscWaveSelector);

    setSliderWithLabel(fmFreqSlider, fmFreqLabel, apvts, fmFreqId, fmFreqAttachment);
    setSliderWithLabel(fmDepthSlider, fmDepthLabel, apvts, fmDepthId, fmDepthAttachment);

}

OscComponent::~OscComponent() {}



void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}
void OscComponent::resized()
{

    const auto sliderPosY = 80;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;



    oscWaveSelector.setBounds(0, 0, 90, 20);

    fmFreqSlider.setBounds(0, sliderPosY, sliderWidth, sliderHeight);
    fmFreqLabel.setBounds(
        fmFreqSlider.getX(),
        fmFreqSlider.getY() - labelYOffset,
        fmFreqSlider.getWidth(),
        labelHeight);

    fmDepthSlider.setBounds(fmFreqSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds(
        fmDepthSlider.getX(),
        fmDepthSlider.getY() - labelYOffset,
        fmDepthSlider.getWidth(),
        labelHeight);
}

void OscComponent::setSliderWithLabel(juce::Slider& slider,
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
