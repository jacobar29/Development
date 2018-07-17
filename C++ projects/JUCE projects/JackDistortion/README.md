//============================

Created by Jack Barnes
July 2018
//===========


A distortion plugin built using the JUCE framework and C++. The distortion algorithms used are a part of the JackAudioToolkit.

Distortion type may be selected, currently there are options for:

Symmetrical clipping - all values above the threshold, or below the negative value of the threshold are clipped to the threshold value. this type of clipping is similar to the imfamous ibanez tube screamer.

asymmetrical clipping - all values above the threshold are clipped, negative portion of the wave passes unaffected

fuzz - input signal is scaled using math.h exp() function, the dry signal is added back in to via a blend control. 
the fuzz function needs work to be of any real use, one of the current issue lies in the distorted signal adding to the dry signal and clipping the systems audio output.

an input gain pot controls the distortion functions input level, a volume pot acts as a makeup gain post clipping.
