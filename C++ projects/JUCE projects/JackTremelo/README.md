A simple Tremelo plugin built using Juce and C++.
the oscillator is a part of my JackAudioToolkit, which also contains the tremelo algorithm.

The amplitude of each channel is modulated by a sine wave, the frequency of which is dictated by the rate pot, the amount of modulation is given by the depth.

depth is produced by combining the modulated signal with a portion of the input signal. The modulation wave is scaled by value of the depth pot, and then combined with the input sample scaled by a factor of 1 - depth so that the overall amplitude of the signal is preserved.
