#include "PluginProcessor.h"
#include "PluginEditor.h"

OXC3AudioProcessor::OXC3AudioProcessor()
    : AudioProcessor (BusesProperties()
        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "Parameters", createParameterLayout())
{
}

juce::AudioProcessorValueTreeState::ParameterLayout OXC3AudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back (std::make_unique<juce::AudioParameterFloat>
    (
        "input",
        "Input",
        juce::NormalisableRange<float> (0.0f, 4.0f, 0.001f),
        1.0f
    ));

    params.push_back (std::make_unique<juce::AudioParameterFloat>
    (
        "output",
        "Output",
        juce::NormalisableRange<float> (0.0f, 4.0f, 0.001f),
        1.0f
    ));

    params.push_back (std::make_unique<juce::AudioParameterFloat>
    (
        "drive",
        "Drive",
        juce::NormalisableRange<float> (0.001f, 200.0f, 0.001f),
        22.0f
    ));

    params.push_back (std::make_unique<juce::AudioParameterFloat>
    (
        "atiming",
        "A Timing",
        juce::NormalisableRange<float> (0.001f, 0.05f, 0.000001f),
        0.004f
    ));

    params.push_back (std::make_unique<juce::AudioParameterFloat>
    (
        "btiming",
        "B Timing",
        juce::NormalisableRange<float> (0.001f, 0.05f, 0.000001f),
        0.001f
    ));

    params.push_back (std::make_unique<juce::AudioParameterBool>
    (
        "delta",
        "Delta",
        false
    ));

    return { params.begin(), params.end() };
}

void OXC3AudioProcessor::prepareToPlay (double, int)
{
    a = 1.0f;
    b = 1.0f;
}

void OXC3AudioProcessor::releaseResources()
{
}

bool OXC3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo()
        && layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void OXC3AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    auto* left  = buffer.getWritePointer (0);
    auto* right = buffer.getWritePointer (1);

    const float input   = apvts.getRawParameterValue ("input")->load();
    const float output  = apvts.getRawParameterValue ("output")->load();
    const float drive   = apvts.getRawParameterValue ("drive")->load();
    const float atiming = apvts.getRawParameterValue ("atiming")->load();
    const float btiming = apvts.getRawParameterValue ("btiming")->load();
    const bool delta    = apvts.getRawParameterValue ("delta")->load() > 0.5f;

    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        float l = left[i]  * input;
        float r = right[i] * input;

        float mid = l * 0.5f + r * 0.5f;
float dist = std::abs (a - b) / (a + b);

float aTime = atiming + dist;
float bTime = btiming + dist;

a = (1.0f - aTime) * b
  + aTime * std::abs ((mid * mid)) * drive / a;

b = (1.0f - bTime) * a
  + std::abs (a - b) / (1.0f + std::abs (a - b))
  + bTime * std::pow (b, 1.0f - dist);

        float outL = l / b;
        float outR = r / b;

        if (delta)
        {
            left[i]  = l - outL;
            right[i] = r - outR;
        }
        else
        {
            left[i]  = outL * output;
            right[i] = outR * output;
        }
    }
}

void OXC3AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void OXC3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary (data, sizeInBytes));

    if (xml != nullptr && xml->hasTagName (apvts.state.getType()))
        apvts.replaceState (juce::ValueTree::fromXml (*xml));
}

juce::AudioProcessorEditor* OXC3AudioProcessor::createEditor()
{
    return new OXC3AudioProcessorEditor (*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OXC3AudioProcessor();
}