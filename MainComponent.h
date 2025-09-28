#pragma once

#include <JuceHeader.h>
#include "VisualAnalyzer.h"




class MainComponent : public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void resized() override;

private:

    VisualAnalyzer visualAnalyzer;

    // === UI COMPONENTS ===
    juce::Slider gainSlider;
    juce::Label gainLabel;

    juce::ToggleButton distortionToggle;

    juce::ToggleButton delayToggle;
    juce::Slider delayTimeSlider;
    juce::Label delayTimeLabel;

    juce::Slider feedbackSlider;
    juce::Label feedbackLabel;

    juce::Slider delayMixSlider;
    juce::Label delayMixLabel;

    juce::ToggleButton reverbToggle;
    juce::Slider reverbMixSlider;
    juce::Label reverbMixLabel;

    juce::Slider tremoloRateSlider;
    juce::Slider tremoloDepthSlider;
    juce::ComboBox tremoloWaveformBox;

    juce::Label tremoloRateLabel;
    juce::Label tremoloDepthLabel;
    juce::Label tremoloWaveformLabel;
    juce::ToggleButton tremoloToggle;


    // === Auto-Pan UI ===
    juce::ToggleButton autoPanToggle;

    juce::Slider autoPanRateSlider;
   // juce::Label autoPanRateLabel;

    juce::Slider autoPanDepthSlider;
   // juce::Label autoPanDepthLabel;

    // === EQ (Filter) ===
    juce::ToggleButton filterToggle;
    juce::ComboBox filterTypeBox; // 1: Low-pass, 2: High-pass
    juce::Slider cutoffSlider, resonanceSlider;
    juce::Label filterTypeLabel, cutoffLabel, resonanceLabel;

    juce::dsp::StateVariableTPTFilter<float> filterL, filterR;
    juce::GroupComponent gainGroup, distortionGroup, delayGroup, reverbGroup, tremoloGroup, autoPanGroup, filterGroup;
    juce::Label autoPanRateLabel, autoPanDepthLabel;


    // === DSP Variables ===
    double sampleRate = 44100.0; // initialized to default, updated in prepareToPlay

    float autoPanPhase = 0.0f;
    float autoPanRate = 2.0f;
    float autoPanDepth = 0.5f;

    float tremoloPhase = 0.0f;

    // === Delay ===
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLineLeft{ 44100 };
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLineRight{ 44100 };

    // === Reverb ===
    juce::dsp::Reverb reverb;
    juce::dsp::Reverb::Parameters reverbParams;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
    
};
