#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // === Gain ===
    gainSlider.setRange(0.0, 10.0, 0.01);
    gainSlider.setValue(1.0);
    addAndMakeVisible(gainSlider);
    gainLabel.setText("Gain", juce::dontSendNotification);
    addAndMakeVisible(gainLabel);

    // === Distortion ===
    distortionToggle.setButtonText("Enable Distortion");
    addAndMakeVisible(distortionToggle);

    // === Delay ===
    delayToggle.setButtonText("Enable Delay");
    addAndMakeVisible(delayToggle);

    delayTimeSlider.setRange(1.0, 2000.0, 1.0);
    delayTimeSlider.setValue(500.0);
    addAndMakeVisible(delayTimeSlider);
    delayTimeLabel.setText("Delay Time (ms)", juce::dontSendNotification);
    addAndMakeVisible(delayTimeLabel);

    feedbackSlider.setRange(0.0, 0.95, 0.01);
    feedbackSlider.setValue(0.5);
    addAndMakeVisible(feedbackSlider);
    feedbackLabel.setText("Feedback", juce::dontSendNotification);
    addAndMakeVisible(feedbackLabel);

    delayMixSlider.setRange(0.0, 1.0, 0.01);
    delayMixSlider.setValue(0.5);
    addAndMakeVisible(delayMixSlider);
    delayMixLabel.setText("Delay Mix", juce::dontSendNotification);
    addAndMakeVisible(delayMixLabel);

    // === Reverb ===
    reverbToggle.setButtonText("Enable Reverb");
    addAndMakeVisible(reverbToggle);

    reverbMixSlider.setRange(0.0, 1.0, 0.01);
    reverbMixSlider.setValue(0.3);
    addAndMakeVisible(reverbMixSlider);
    reverbMixLabel.setText("Reverb Wet", juce::dontSendNotification);
    addAndMakeVisible(reverbMixLabel);

    // === Tremolo ===
    tremoloToggle.setButtonText("Enable Tremolo");
    addAndMakeVisible(tremoloToggle);

    tremoloRateSlider.setRange(0.1, 20.0, 0.1);
    tremoloRateSlider.setValue(5.0);
    addAndMakeVisible(tremoloRateSlider);
    tremoloRateLabel.setText("Rate (Hz)", juce::dontSendNotification);
    tremoloRateLabel.attachToComponent(&tremoloRateSlider, false);
    tremoloRateLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(tremoloRateLabel);

    tremoloDepthSlider.setRange(0.0, 1.0, 0.01);
    tremoloDepthSlider.setValue(0.5);
    addAndMakeVisible(tremoloDepthSlider);
    tremoloDepthLabel.setText("Depth", juce::dontSendNotification);
    tremoloDepthLabel.attachToComponent(&tremoloDepthSlider, false);
    tremoloDepthLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(tremoloDepthLabel);

    tremoloWaveformBox.addItem("Sine", 1);
    tremoloWaveformBox.addItem("Square", 2);
    tremoloWaveformBox.addItem("Triangle", 3);
    tremoloWaveformBox.setSelectedId(1);
    addAndMakeVisible(tremoloWaveformBox);
    tremoloWaveformLabel.setText("Waveform", juce::dontSendNotification);
    tremoloWaveformLabel.attachToComponent(&tremoloWaveformBox, false);
    tremoloWaveformLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(tremoloWaveformLabel);

    // === AutoPan ===
    autoPanToggle.setButtonText("Enable Auto-Pan");
    addAndMakeVisible(autoPanToggle);

    autoPanRateSlider.setRange(0.1, 10.0, 0.1);
    autoPanRateSlider.setValue(2.0);
    autoPanRateSlider.onValueChange = [this] {
        autoPanRate = autoPanRateSlider.getValue();
        };
    addAndMakeVisible(autoPanRateSlider);
    autoPanRateLabel.setText("Rate (Hz)", juce::dontSendNotification);
    autoPanRateLabel.attachToComponent(&autoPanRateSlider, true);
    addAndMakeVisible(autoPanRateLabel);

    autoPanDepthSlider.setRange(0.0, 1.0, 0.01);
    autoPanDepthSlider.setValue(0.5);
    autoPanDepthSlider.onValueChange = [this] {
        autoPanDepth = autoPanDepthSlider.getValue();
        };
    addAndMakeVisible(autoPanDepthSlider);
    autoPanDepthLabel.setText("Depth", juce::dontSendNotification);
    autoPanDepthLabel.attachToComponent(&autoPanDepthSlider, true);
    addAndMakeVisible(autoPanDepthLabel);

    // === Filter (EQ) ===
    filterToggle.setButtonText("Enable Filter");
    addAndMakeVisible(filterToggle);

    filterTypeBox.addItem("Low-pass", 1);
    filterTypeBox.addItem("High-pass", 2);
    filterTypeBox.setSelectedId(1);
    addAndMakeVisible(filterTypeBox);
    filterTypeLabel.setText("Filter Type", juce::dontSendNotification);
    addAndMakeVisible(filterTypeLabel);

    cutoffSlider.setRange(20.0, 20000.0, 1.0);
    cutoffSlider.setSkewFactorFromMidPoint(1000.0);
    cutoffSlider.setValue(1000.0);
    addAndMakeVisible(cutoffSlider);
    cutoffLabel.setText("Cutoff (Hz)", juce::dontSendNotification);
    addAndMakeVisible(cutoffLabel);

    resonanceSlider.setRange(0.1, 10.0, 0.1);
    resonanceSlider.setValue(1.0);
    addAndMakeVisible(resonanceSlider);
    resonanceLabel.setText("Resonance (Q)", juce::dontSendNotification);
    addAndMakeVisible(resonanceLabel);

    // === Analyzer ===
    addAndMakeVisible(visualAnalyzer);
    visualAnalyzer.startTimerHz(60);  // 60 FPS

    // === Groups ===
    gainGroup.setText("Gain");
    addAndMakeVisible(gainGroup);
    distortionGroup.setText("Distortion");
    addAndMakeVisible(distortionGroup);
    delayGroup.setText("Delay");
    addAndMakeVisible(delayGroup);
    reverbGroup.setText("Reverb");
    addAndMakeVisible(reverbGroup);
    tremoloGroup.setText("Tremolo");
    addAndMakeVisible(tremoloGroup);
    autoPanGroup.setText("Auto-Pan");
    addAndMakeVisible(autoPanGroup);
    filterGroup.setText("Filter");
    addAndMakeVisible(filterGroup);

    // Audio and window setup
    setSize(600, 500);
    setAudioChannels(2, 2);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}


//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double newSampleRate)
{
    sampleRate = newSampleRate;

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlockExpected);
    spec.numChannels = 2;

    delayLineLeft.prepare(spec);
    delayLineRight.prepare(spec);
    delayLineLeft.setMaximumDelayInSamples(44100);
    delayLineRight.setMaximumDelayInSamples(44100);
    //juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32>(samplesPerBlockExpected), 1 };

    filterL.prepare(spec);
    filterR.prepare(spec);


    reverb.prepare({ sampleRate, static_cast<juce::uint32>(samplesPerBlockExpected), 2 });
}

void MainComponent::releaseResources()
{
    // No dynamic resources to release
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* buffer = bufferToFill.buffer;
    const int numSamples = bufferToFill.numSamples;

    float gain = static_cast<float>(gainSlider.getValue());

    // === Distortion ===
    if (distortionToggle.getToggleState())
    {
        for (int channel = 0; channel < buffer->getNumChannels(); ++channel)
        {
            auto* data = buffer->getWritePointer(channel, bufferToFill.startSample);
            for (int sample = 0; sample < numSamples; ++sample)
                data[sample] = std::tanh(data[sample] * gain);
        }
    }

    // === Delay ===
    if (delayToggle.getToggleState())
    {
        float delayTimeMs = static_cast<float>(delayTimeSlider.getValue());
        float feedback = static_cast<float>(feedbackSlider.getValue());
        float mix = static_cast<float>(delayMixSlider.getValue());
        int delaySamples = static_cast<int>((delayTimeMs / 1000.0f) * sampleRate);

        delayLineLeft.setDelay(delaySamples);
        delayLineRight.setDelay(delaySamples);

        for (int i = 0; i < numSamples; ++i)
        {
            float inL = buffer->getReadPointer(0)[i];
            float inR = buffer->getNumChannels() > 1 ? buffer->getReadPointer(1)[i] : inL;

            float delayedL = delayLineLeft.popSample(0);
            float delayedR = delayLineRight.popSample(0);

            float outL = inL * (1.0f - mix) + delayedL * mix;
            float outR = inR * (1.0f - mix) + delayedR * mix;

            delayLineLeft.pushSample(0, inL + delayedL * feedback);
            delayLineRight.pushSample(0, inR + delayedR * feedback);

            buffer->getWritePointer(0)[i] = outL;
            if (buffer->getNumChannels() > 1)
                buffer->getWritePointer(1)[i] = outR;
        }
    }

    // === Reverb ===
    if (reverbToggle.getToggleState())
    {
        reverbParams.wetLevel = static_cast<float>(reverbMixSlider.getValue());
        reverbParams.dryLevel = 1.0f - reverbParams.wetLevel;
        reverbParams.roomSize = 0.5f;
        reverbParams.damping = 0.5f;
        reverbParams.width = 1.0f;
        reverb.setParameters(reverbParams);

        juce::dsp::AudioBlock<float> block(*buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        reverb.process(context);
    }

    // === Filter (EQ) ===
    if (filterToggle.getToggleState())
    {
        auto type = filterTypeBox.getSelectedId() == 1
            ? juce::dsp::StateVariableTPTFilterType::lowpass
            : juce::dsp::StateVariableTPTFilterType::highpass;

        float cutoff = static_cast<float>(cutoffSlider.getValue());
        float resonance = static_cast<float>(resonanceSlider.getValue());

        filterL.setType(type);
        filterR.setType(type);
        filterL.setCutoffFrequency(cutoff);
        filterR.setCutoffFrequency(cutoff);
        filterL.setResonance(resonance);
        filterR.setResonance(resonance);

        juce::dsp::AudioBlock<float> block(*buffer);
        juce::dsp::AudioBlock<float> left = block.getSingleChannelBlock(0);
        juce::dsp::AudioBlock<float> right = buffer->getNumChannels() > 1 ? block.getSingleChannelBlock(1) : left;

        filterL.process(juce::dsp::ProcessContextReplacing<float>(left));
        filterR.process(juce::dsp::ProcessContextReplacing<float>(right));
    }


    // === Tremolo ===
    if (tremoloToggle.getToggleState())
    {
        float rate = static_cast<float>(tremoloRateSlider.getValue());
        float depth = static_cast<float>(tremoloDepthSlider.getValue());
        int waveform = tremoloWaveformBox.getSelectedId();

        auto* buffer = bufferToFill.buffer;
        int numSamples = bufferToFill.numSamples;
        int sampleRate = this->sampleRate;


        for (int channel = 0; channel < buffer->getNumChannels(); ++channel)
        {
            float* data = buffer->getWritePointer(channel, bufferToFill.startSample);

            for (int sample = 0; sample < numSamples; ++sample)
            {
                float t = tremoloPhase / sampleRate;
                float mod = 0.0f;

                switch (waveform)
                {
                case 1: // Sine
                    mod = std::sin(2.0f * juce::MathConstants<float>::pi * rate * t);
                    break;
                case 2: // Square
                    mod = std::sin(2.0f * juce::MathConstants<float>::pi * rate * t) > 0 ? 1.0f : -1.0f;
                    break;
                case 3: // Triangle
                    mod = 2.0f * std::abs(2.0f * (rate * t - std::floor(rate * t + 0.5f))) - 1.0f;
                    break;
                }

                float gain = 1.0f - (depth * ((mod + 1.0f) / 2.0f));
                data[sample] *= gain;

                tremoloPhase += 1.0f;
                if (tremoloPhase >= sampleRate)
                    tremoloPhase -= sampleRate;
            }
        }
    }
    visualAnalyzer.pushBuffer(*bufferToFill.buffer);



    // === Auto-Pan ===
    if (autoPanToggle.getToggleState())
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            float lfo = std::sin(2.0f * juce::MathConstants<float>::pi * autoPanPhase);
            float panLeft = 0.5f * (1.0f - autoPanDepth * lfo);
            float panRight = 0.5f * (1.0f + autoPanDepth * lfo);

            for (int channel = 0; channel < buffer->getNumChannels(); ++channel)
            {
                float* data = buffer->getWritePointer(channel);
                if (channel == 0)
                    data[sample] *= panLeft;
                else if (channel == 1)
                    data[sample] *= panRight;
            }

            autoPanPhase += autoPanRate / sampleRate;
            if (autoPanPhase >= 1.0f)
                autoPanPhase -= 1.0f;
        }
    }
    for (int channel = 0; channel < buffer->getNumChannels(); ++channel)
    {
        auto* channelData = buffer->getReadPointer(channel);
        for (int sample = 0; sample < buffer->getNumSamples(); ++sample)
        {
            float inputSample = channelData[sample];

            // For visualization
            if (scopeData.size() < 512)
                scopeData.push_back(inputSample);
            else
            {
                scopeData.erase(scopeData.begin());
                scopeData.push_back(inputSample);
            }
        }
    }
}


    void MainComponent::resized()
    {
        int margin = 10;
        int labelWidth = 100;
        int sliderWidth = 200;
        int sliderHeight = 40;
        int toggleHeight = 30;
        int labelHeight = 20;
        int y = margin;

        // Gain
        gainLabel.setBounds(margin, y, labelWidth, labelHeight);
        gainSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
        y += sliderHeight + margin;

        // Distortion Toggle
        distortionToggle.setBounds(margin, y, labelWidth + sliderWidth, toggleHeight);
        y += toggleHeight + margin;

        // Delay Section
        delayToggle.setBounds(margin, y, labelWidth + sliderWidth, toggleHeight);
        y += toggleHeight + margin;

        delayTimeLabel.setBounds(margin, y, labelWidth, labelHeight);
        delayTimeSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
        y += sliderHeight + margin;

        feedbackLabel.setBounds(margin, y, labelWidth, labelHeight);
        feedbackSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
        y += sliderHeight + margin;

        delayMixLabel.setBounds(margin, y, labelWidth, labelHeight);
        delayMixSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
        y += sliderHeight + margin;

        // Reverb Section
        reverbToggle.setBounds(margin, y, labelWidth + sliderWidth, toggleHeight);
        y += toggleHeight + margin;

        reverbMixLabel.setBounds(margin, y, labelWidth, labelHeight);
        reverbMixSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
        y += sliderHeight + margin;

        // Auto-Pan Section
        autoPanToggle.setBounds(margin, y, labelWidth + sliderWidth, toggleHeight);
        y += toggleHeight + margin;

        autoPanRateLabel.setBounds(margin, y, labelWidth, labelHeight);
        autoPanRateSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
        y += sliderHeight + margin;

        autoPanDepthLabel.setBounds(margin, y, labelWidth, labelHeight);
        autoPanDepthSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
        y += sliderHeight + margin;

        // Tremolo Section
        tremoloToggle.setBounds(margin, y, 200, 30);
        y += 40;

        tremoloRateLabel.setBounds(margin, y, 100, 20);
        tremoloRateSlider.setBounds(120, y, 200, sliderHeight);
        y += sliderHeight + margin;

        tremoloDepthLabel.setBounds(margin, y, 100, 20);
        tremoloDepthSlider.setBounds(120, y, 200, sliderHeight);
        y += sliderHeight + margin;

        tremoloWaveformLabel.setBounds(margin, y, 150, 20);
        tremoloWaveformBox.setBounds(160, y, 160, sliderHeight);
        y += sliderHeight + margin;

        // Filter Section
        filterToggle.setBounds(margin, y, labelWidth + sliderWidth, toggleHeight);
        y += toggleHeight + margin;

        filterTypeLabel.setBounds(margin, y, labelWidth, labelHeight);
        filterTypeBox.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
        y += sliderHeight + margin;

        cutoffLabel.setBounds(margin, y, labelWidth, labelHeight);
        cutoffSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
        y += sliderHeight + margin;

        resonanceLabel.setBounds(margin, y, labelWidth, labelHeight);
        resonanceSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
        y += sliderHeight + margin;

        // Visual Analyzer placement
        visualAnalyzer.setBounds(getWidth() - 310, 10, 300, 150);
    }



