#pragma once

#include "BinaryData.h"
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/FilterComponent.h"
#include "UI/OscComponent.h"
#include "melatonin_inspector/melatonin_inspector.h"

//==============================================================================
class PluginEditor : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor (PluginProcessor&);
    ~PluginEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

private:
    PluginProcessor& processorRef;

    std::unique_ptr<melatonin::Inspector> inspector;
    juce::TextButton inspectButton { "Inspect the UI" };

    OscComponent osc;
    AdsrComponent adsr;
    FilterComponent filter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
