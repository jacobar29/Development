JackAudioToolkit is a collection of tools for audio synthesis and manipulation.

This includes:

//=====================================================================

JackSynthesis:
	JackOsc - an oscillator with options for sin/square/saw/triangle wave and white noise generation
	JackEnv - a simple ADSR envelope
	JackFilter - A low / high pass filter with resonance and cutoff variables, currently based on the maximilian maxifilter algorithm, soon to be replaced with one of my own but until then many thanks to the maximilian devs at https://github.com/micknoise/Maximilian

//=====================================================================

JackDsp:
	JackDistortion - various algorithms for signal clpping and distortion, currently has functions for Asymmetrical and symettrical hard clipping and a fuzz effect. Soft clipping and modifications to the fuzz to increase its usefulness are planned

	JackEffects - a tremelo and a simple delay plugin. more will be added as and when i finish them up.
	