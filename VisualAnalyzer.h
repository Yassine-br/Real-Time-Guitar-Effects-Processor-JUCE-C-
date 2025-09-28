#pragma once

#include <JuceHeader.h>
#include <vector>

extern std::vector<float> scopeData;

static constexpr int fftOrder = 11;
static constexpr int fftSize = 1 << fftOrder;

class VisualAnalyzer : public juce::Component,
    public juce::Timer  // changed from private to public
{
public:
    VisualAnalyzer();
    void pushBuffer(const juce::AudioBuffer<float>& buffer);
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void timerCallback() override;
    void drawFrame(juce::Graphics& g);

    static constexpr float referenceDecibels = -60.0f;
    
    juce::dsp::FFT forwardFFT;
    juce::dsp::WindowingFunction<float> window;

    std::vector<float> fifo;
    std::vector<float> fftData;
    std::vector<float> smoothedFFTData;
    int fifoIndex = 0;
    bool nextFFTBlockReady = false;
    float smoothingFactor = 0.8f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualAnalyzer)
};
