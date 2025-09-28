#include "VisualAnalyzer.h"

using namespace juce;

std::vector<float> scopeData;

VisualAnalyzer::VisualAnalyzer()
    : forwardFFT(fftOrder), window(fftSize, dsp::WindowingFunction<float>::hann)
{
    fifo.resize(fftSize);
    fftData.resize(2 * fftSize);
    smoothedFFTData.resize(fftSize / 2, 0.0f);
    startTimerHz(60);  // Refresh 60 times per second
}

void VisualAnalyzer::pushBuffer(const AudioBuffer<float>& buffer)
{
    auto* channelData = buffer.getReadPointer(0);
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        fifo[fifoIndex++] = channelData[i];

        if (fifoIndex == fftSize)
        {
            std::copy(fifo.begin(), fifo.end(), fftData.begin());
            window.multiplyWithWindowingTable(fftData.data(), fftSize);
            forwardFFT.performFrequencyOnlyForwardTransform(fftData.data());
            nextFFTBlockReady = true;
            fifoIndex = 0;
        }
    }
}

void VisualAnalyzer::timerCallback()
{
    if (nextFFTBlockReady)
    {
        nextFFTBlockReady = false;

        for (int i = 0; i < fftSize / 2; ++i)
        {
            float level = Decibels::gainToDecibels(fftData[i]) - referenceDecibels;
            level = jlimit(0.0f, 1.0f, level / 60.0f);  // Normalize to [0, 1]
            smoothedFFTData[i] = smoothingFactor * smoothedFFTData[i] + (1.0f - smoothingFactor) * level;
        }

        repaint();
    }
}

void VisualAnalyzer::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    const int width = getWidth();
    const int height = getHeight();
    const float maxMagnitude = 10.0f; // adjust this as needed

    for (int i = 0; i < fftSize / 2; ++i)
    {
        float magnitude = fftData[i];
        float scaledHeight = juce::jmap(magnitude, 0.0f, maxMagnitude, 0.0f, (float)height);

        float x = i * (float)width / (fftSize / 2);
        float w = (float)width / (fftSize / 2);

        g.setColour(juce::Colour::fromHSV(magnitude / maxMagnitude, 1.0f, 1.0f, 1.0f));
        g.fillRect(x, height - scaledHeight, w, scaledHeight);
    }
}




void VisualAnalyzer::resized()
{
    // No dynamic layout needed for now
}

void VisualAnalyzer::drawFrame(Graphics& g)
{
    auto width = getLocalBounds().getWidth();
    auto height = getLocalBounds().getHeight();

    Path p;
    p.startNewSubPath(0, height);

    for (int i = 0; i < smoothedFFTData.size(); ++i)
    {
        float x = static_cast<float>(i) / smoothedFFTData.size() * width;
        float y = height - smoothedFFTData[i] * height;
        p.lineTo(x, y);
    }

    p.lineTo(width, height);
    p.closeSubPath();

    g.setColour(Colours::limegreen);
    g.fillPath(p);
}



