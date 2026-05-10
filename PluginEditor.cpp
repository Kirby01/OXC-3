#include "PluginEditor.h"

OXC3AudioProcessorEditor::OXC3AudioProcessorEditor (OXC3AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (620, 300);

    titleLabel.setText ("OXC-3 Dynamic Leveling Amplifier", juce::dontSendNotification);
    titleLabel.setJustificationType (juce::Justification::centred);
    titleLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    titleLabel.setFont (juce::Font (22.0f, juce::Font::bold));
    addAndMakeVisible (titleLabel);

    setupSlider (inputSlider, inputLabel, "Input");
    setupSlider (outputSlider, outputLabel, "Output");
    setupSlider (driveSlider, driveLabel, "Drive");
    setupSlider (aTimingSlider, aTimingLabel, "A Timing");
    setupSlider (bTimingSlider, bTimingLabel, "B Timing");

    deltaButton.setButtonText ("Delta");
    deltaButton.setColour (juce::ToggleButton::textColourId, juce::Colours::white);
    addAndMakeVisible (deltaButton);

    inputAttachment   = std::make_unique<SliderAttachment> (audioProcessor.apvts, "input", inputSlider);
    outputAttachment  = std::make_unique<SliderAttachment> (audioProcessor.apvts, "output", outputSlider);
    driveAttachment   = std::make_unique<SliderAttachment> (audioProcessor.apvts, "drive", driveSlider);
    aTimingAttachment = std::make_unique<SliderAttachment> (audioProcessor.apvts, "atiming", aTimingSlider);
    bTimingAttachment = std::make_unique<SliderAttachment> (audioProcessor.apvts, "btiming", bTimingSlider);
    deltaAttachment   = std::make_unique<ButtonAttachment> (audioProcessor.apvts, "delta", deltaButton);
}

void OXC3AudioProcessorEditor::setupSlider (juce::Slider& slider, juce::Label& label, const juce::String& text)
{
    slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    slider.setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    slider.setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::orange);
    slider.setColour (juce::Slider::thumbColourId, juce::Colours::white);
    addAndMakeVisible (slider);

    label.setText (text, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    label.setColour (juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible (label);
}

void OXC3AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour::fromRGB (20, 20, 24));

    g.setColour (juce::Colours::orange.withAlpha (0.25f));
    g.drawRoundedRectangle (getLocalBounds().toFloat().reduced (10.0f), 14.0f, 2.0f);

    g.setColour (juce::Colours::white.withAlpha (0.55f));
    g.setFont (14.0f);
    g.drawFittedText ("by Harmonious Records", 0, 258, getWidth(), 24, juce::Justification::centred, 1);
}

void OXC3AudioProcessorEditor::resized()
{
    titleLabel.setBounds (20, 18, getWidth() - 40, 34);

    const int top = 80;
    const int sliderW = 105;
    const int sliderH = 135;
    const int gap = 14;
    const int startX = 25;

    auto place = [&] (juce::Slider& s, juce::Label& l, int index)
    {
        int x = startX + index * (sliderW + gap);
        l.setBounds (x, top - 24, sliderW, 20);
        s.setBounds (x, top, sliderW, sliderH);
    };

    place (inputSlider, inputLabel, 0);
    place (outputSlider, outputLabel, 1);
    place (driveSlider, driveLabel, 2);
    place (aTimingSlider, aTimingLabel, 3);
    place (bTimingSlider, bTimingLabel, 4);

    deltaButton.setBounds (260, 220, 100, 28);
}