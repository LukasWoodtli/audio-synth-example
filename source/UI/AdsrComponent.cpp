//
// Created by Lukas Woodtli on 01.04.2024.
//

#include <juce_audio_processors/juce_audio_processors.h>
#include "AdsrComponent.h"

AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    attackAttachment = std::make_unique<SliderAttachment> (apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment> (apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment> (apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment> (apvts, "RELEASE", releaseSlider);

    setSliderParams (attackSlider);
    setSliderParams (decaySlider);
    setSliderParams (sustainSlider);
    setSliderParams (releaseSlider);
}

void AdsrComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

}

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;

    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

void AdsrComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}