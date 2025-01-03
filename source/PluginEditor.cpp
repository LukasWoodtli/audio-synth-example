#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p),
      osc(processorRef.getAudioProcessorValueTreeState(),
          "OSC1WAVETYPE",
          "OSC1FMFREQ",
          "OSC1FMDEPTH"),
      adsr(processorRef.getAudioProcessorValueTreeState()),
      filter(processorRef.getAudioProcessorValueTreeState(),
          "FILTERTYPE",
          "FILTERCUTOFF",
          "FILTERRES")
{
    juce::ignoreUnused (processorRef);

    addAndMakeVisible (inspectButton);

    // this chunk of code instantiates and opens the melatonin inspector
    inspectButton.onClick = [&] {
        if (!inspector)
        {
            inspector = std::make_unique<melatonin::Inspector> (*this);
            inspector->onClose = [this]() { inspector.reset(); };
        }

        inspector->setVisible (true);
    };

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);

    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
}

PluginEditor::~PluginEditor()
{
}

void PluginEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void PluginEditor::resized()
{
    auto area = getLocalBounds();
    area.removeFromBottom(50);
    inspectButton.setBounds (10, 50, 50, 30);

    // set Osc bounds
    osc.setBounds(10, 10, 200, 200);
    // set ADSR bounds
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
    // set filter bounds
    filter.setBounds(10, osc.getBottom(), getWidth() / 2, getHeight());

}
