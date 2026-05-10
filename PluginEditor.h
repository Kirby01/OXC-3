#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class OXC3AudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    OXC3AudioProcessorEditor (OXC3AudioProcessor&);
    ~OXC3AudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    OXC3AudioProcessor& audioProcessor;

    juce::Label titleLabel;

    juce::Slider inputSlider, outputSlider, driveSlider, aTimingSlider, bTimingSlider;
    juce::Label inputLabel, outputLabel, driveLabel, aTimingLabel, bTimingLabel;

    juce::ToggleButton deltaButton;

    std::unique_ptr<SliderAttachment> inputAttachment;
    std::unique_ptr<SliderAttachment> outputAttachment;
    std::unique_ptr<SliderAttachment> driveAttachment;
    std::unique_ptr<SliderAttachment> aTimingAttachment;
    std::unique_ptr<SliderAttachment> bTimingAttachment;
    std::unique_ptr<ButtonAttachment> deltaAttachment;

    void setupSlider (juce::Slider& slider, juce::Label& label, const juce::String& text);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OXC3AudioProcessorEditor)
};