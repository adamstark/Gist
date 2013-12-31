Gist - Usage in C++
==================================

**[Version 0.1.0]**

This document provides some code snippets showing how the Gist library can be used in practice in C++.

Firstly, to use all the features of Gist you must include the Gist.h header file:

	#include "Gist.h"

We will now look at each of the modules in turn. Note that the Gist classes are template classes and here we have used them with floats, but they could just as easily be used with doubles.

Core Time Domain Features
=========================

**Using vectors:**

	CoreTimeDomainFeatures<float> tdf;
    
    std::vector<float> frame;
    
    // !
    // (some code here to create an audio frame in
    // vector format)
    // !
    
    // --------------------------------------------------
    // calculate RMS
    float rms = tdf.rootMeanSquare(frame);

    // --------------------------------------------------    
    // calculate Peak Energy
    float p = tdf.peakEnergy(frame);
    
    // --------------------------------------------------    
    // calculate Zero Crossing Rate
    float zcr = tdf.zeroCrossingRate(frame);
    
**Using arrays:**

	CoreTimeDomainFeatures<float> tdf;
    
    int N = 512;
    
    double frame[N];
    
    // !
    // (some code here to fill the array audio frame in
    // array format)
    // !
    
    // --------------------------------------------------
    // calculate RMS
    float rms = tdf.rootMeanSquare(frame,N);

    // --------------------------------------------------    
    // calculate Peak Energy
    float p = tdf.peakEnergy(frame,N);
    
    // --------------------------------------------------    
    // calculate Zero Crossing Rate
    float zcr = tdf.zeroCrossingRate(frame,N);
    
    
Core Frequency Domain Features
==============================

**Using vectors:**

	CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> magnitudeSpectrum;
    
    // !
    // (some code here to calculate the FFT and the magnitude spectrum/
    // Note that the magnitude spectrum should contain the first half
    // of the magnitude spectrum and not the whole mirrored spectrum)
    // !
    
    // --------------------------------------------------
    // calculate Spectral Centroid
    float sc = fdf.spectralCentroid(magnitudeSpectrum);

    
**Using arrays:**

	CoreFrequencyDomainFeatures<float> fdf;
    
    int N = 512;
    
    float magnitudeSpectrum[N];
    
    // !
    // (some code here to calculate the FFT and the magnitude spectrum
    // Note that the magnitude spectrum should contain the first half
    // of the magnitude spectrum and not the whole mirrored spectrum)
    // !
    
    // --------------------------------------------------
    // calculate Spectral Centroid
    float sc = fdf.spectralCentroid(magnitudeSpectrum,N);
    
Onset Detection Functions
=========================

**Using vectors:**

	int frameSize = 512;
    
    OnsetDetectionFunction<float> odf(frameSize);
    
    std::vector<float> magnitudeSpectrum;
    
    // !
    // (some code here to calculate the FFT and the magnitude spectrum
    // Note that the magnitude spectrum should contain the first half
    // of the magnitude spectrum and not the whole mirrored spectrum)
    // !
    
    // --------------------------------------------------
    // calculate the Spectral Difference
    float sd = odf.spectralDifference(magnitudeSpectrum);
    
    // --------------------------------------------------
    // calculate the Spectral Difference (half-wave rectified)
    float sdhwr = odf.spectralDifferenceHWR(magnitudeSpectrum);

    
**Using arrays:**

	int frameSize = 512;
    
    OnsetDetectionFunction<float> odf(frameSize);
        
    float magnitudeSpectrum[frameSize];
    
    // !
    // (some code here to calculate the FFT and the magnitude spectrum
    // Note that the magnitude spectrum should contain the first half
    // of the magnitude spectrum and not the whole mirrored spectrum)
    // !
    
    // --------------------------------------------------
    // calculate the Spectral Difference
    float sd = odf.spectralDifference(magnitudeSpectrum,frameSize);
    
    // --------------------------------------------------
    // calculate the Spectral Difference (half-wave rectified)            
    float sdhwr = odf.spectralDifferenceHWR(magnitudeSpectrum,frameSize);
    
    
Pitch Detection with Yin
========================

**Using vectors:**

	int sampleRate = 44100;

	Yin<float> y(sampleRate);
    
    std::vector<float> frame;
    
    // !
    // some code here to fill the frame with audio samples
    // !
    
    float r = y.pitchYin(frame);

**Using arrays:**

	int sampleRate = 44100;
	int frameSize = 512;

	Yin<float> y(sampleRate);
    
    float frame[frameSize];
    
    // !
    // some code here to fill the frame with audio samples
    // !
    
    float r = y.pitchYin(frame,frameSize);