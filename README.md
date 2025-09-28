<img width="1917" height="1019" alt="gui png" src="https://github.com/user-attachments/assets/2462fb4f-9be8-4c9c-9b7f-690a311a1a9d" />
🎸 Real-Time Guitar Effects Processor

This project is a real-time guitar effects processor built with JUCE and C++.
It provides a simple but powerful framework to apply audio effects (gain, distortion, delay, reverb, tremolo, auto-pan, EQ, and more) to a live guitar input signal, with a responsive GUI for control and an integrated audio visualizer.

🚀 Features:

Gain Control – Adjust input/output volume.

Distortion – Add crunch and overdrive.

Delay – Echo effect with adjustable time.

Reverb – Simulates natural room/space acoustics.

Tremolo – Volume modulation with rate, depth, and waveform controls.

Auto-Pan – Stereo modulation effect.

Filter (EQ) – Shape the tone with a simple equalizer.

Audio Visualizer – Real-time waveform/frequency display.

🛠️ Technologies Used:

Projucer

JUCE Framework (C++ library for audio, GUI, and plugins)

C++

Visual Studio 2022

⚙️ How It Works:

The app creates an audio device (input = guitar, output = speakers/headphones).

prepareToPlay() sets up buffers and sample rate.

getNextAudioBlock() processes incoming audio in real time, applying effects.

resized() handles GUI layout for effect controls and visualizer.


