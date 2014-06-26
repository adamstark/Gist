Gist - A Real-Time Audio Analysis Library
==================================

*Version 1.0.1*

Gist is a C++ based audio analysis library, written for use in real-time applications.

Author
------

Gist is written and maintained by Adam Stark.

[http://www.adamstark.co.uk](http://www.adamstark.co.uk)

Usage
-----

Firstly, import the Gist header file:

	#include "Gist.h"
	
##### Instantiation	

Gist is a template class, so instantiate it with floating point precision:

	int frameSize = 512;
	int sampleRate = 44100;

	Gist<float> gist(frameSize,sampleRate);
	
Or with double precision:

	Gist<double> gist(frameSize,sampleRate);

We proceed with the documentation as if we were using floating point precision.

##### Process Audio Frames		

Once you have an audio frame, pass it to the Gist object. You can do this either as a STL vector:
	
	std::vector<float> audioFrame;
	
	// !
	// fill audio frame with samples here
	// !
	
	gist.processAudioFrame(audioFrame);
	
Or, as an array:

	float audioFrame[512];
	
	// !
	// fill audio frame with samples here
	// !
	
	gist.processAudioFrame(audioFrame,512);
	
Now we can retrieve some audio features.
	
##### Core Time Domain Features
	
	// Root Mean Square (RMS)
	float rms = gist.rootMeanSquare();
	
	// Peak Energy
	float peakEnergy = gist.peakEnergy();
	
	// Zero Crossing rate
	float zcr = gist.zeroCrossingRate();
	
##### Core Frequency Domain Features
	
	// Spectral Centroid
	float specCent = gist.spectralCentroid();
	
    // Spectral Crest
    float specCrest = gist.spectralCrest();
    
    // Spectral Flatness
    float specFlat = gist.spectralFlatness();
    

##### Onset Detection Functions
    
    // Energy difference
    float ed = gist.energyDifference();
    
    // Spectral difference
    float sd = gist.spectralDifference();
    
    // Spectral difference (half-wave rectified)
    float sd_hwr = gist.spectralDifferenceHWR();
    
    // Complex Spectral Difference
    float csd = gist.complexSpectralDifference();
    
    // High Frequency Content
    float hfc = gist.highFrequencyContent();
    
##### FFT Magnitude Spectrum

	// FFT Magnitude Spectrum
	std::vector<float> magSpec = gist.getMagnitudeSpectrum();
	
##### Pitch

	// Pitch Estimation
	float pitch = gist.pitchYin();

##### Mel-frequency Representations

	// Mel-frequency Spectrum
	std::vector<float> melSpec = gist.melFrequencySpectrum();
	
	// MFCCs
	std::vector<float> mfcc = gist.melFrequencyCepstralCoefficients();
	
	
Version History
---------------

=== 1.0.1 === (26th June 2014)

* Added the option of using Kiss FFT instead of FFTW

=== 1.0.0 === (22nd June 2014)

* The first version of Gist

Dependencies
------------

The Gist library depends on one of the following FFT libraries:

* [FFTW](http://fftw.org) 

You will need to install this yourself, link projects using -lfftw3 and use the flag -DUSE_FFTW

* [Kiss FFT](http://kissfft.sourceforge.net/) - included with project

This is included with the project. To use Kiss FFT, add the flag -DUSE_FFTW

License
-------

Copyright (c) 2014 Adam Stark

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.



