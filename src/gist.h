//=======================================================================
/** @file Gist.h
 *  @brief Includes all relevant parts of the 'Gist' audio analysis library
 *  @author Adam Stark
 *  @copyright Copyright (C) 2013  Adam Stark
 *
 * This file is part of the 'Gist' audio analysis library
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//=======================================================================


#ifndef __GISTHEADER__
#define __GISTHEADER__

//=======================================================================
// core
#include "core/CoreTimeDomainFeatures.h"
#include "core/CoreFrequencyDomainFeatures.h"

// onset detection functions
#include "onset-detection-functions/OnsetDetectionFunction.h"

// pitch detection
#include "pitch/Yin.h"

// MFCC
#include "mfcc/MFCC.h"

//=======================================================================
// fft
#ifdef USE_FFTW
#include "fftw3.h"
#endif

#ifdef USE_KISS_FFT
#include "kiss_fft.h"
#endif

//=======================================================================
/** Class for all performing all Gist audio analyses */
template <class T>
class Gist
{
public:
    
    /** Constructor
     * @param frameSize_ the input audio frame size
     * @param sampleRate the input audio sample rate
     */
    Gist(int frameSize_,int sampleRate_) :fftConfigured(false), onsetDetectionFunction(frameSize_), yin(sampleRate_), mfcc(frameSize_,sampleRate_)
    {
        setAudioFrameSize(frameSize_);
    }
    
    /** Destructor */
    ~Gist()
    {
        if (fftConfigured)
        {
            freeFFT();
        }
    }

    /** Set the audio frame size.
     * @param frameSize_ the frame size to use
     */
    void setAudioFrameSize(int frameSize_)
    {
        frameSize = frameSize_;

        audioFrame.resize(frameSize);
        fftReal.resize(frameSize);
        fftImag.resize(frameSize);
        magnitudeSpectrum.resize(frameSize/2);
        
        configureFFT();
        
        onsetDetectionFunction.setFrameSize(frameSize);
        mfcc.setFrameSize(frameSize);
    }
    
    /** Process an audio frame
     * @param audioFrame a vector containing audio samples
     */
    void processAudioFrame(std::vector<T> audioFrame_)
    {
        audioFrame = audioFrame_;
        
        performFFT();
    }
    
    /** Process an audio frame
     * @param buffer a pointer to an array containing the audio samples
     * @param numSamples the number of samples in the audio frame
     */
    void processAudioFrame(T *buffer,unsigned long numSamples)
    {
        audioFrame.assign(buffer,buffer + numSamples);
        
        performFFT();
    }
    
    /** Gist automatically calculates the magnitude spectrum when processAudioFrame() is called, this function returns it.
     @returns the current magnitude spectrum */
    std::vector<T> getMagnitudeSpectrum()
    {        
        return magnitudeSpectrum;
    }
    
    //================= CORE TIME DOMAIN FEATURES =================
    
    /** Calculates the root mean square (RMS) of the currently stored audio frame
     * @returns the root mean square (RMS) value
     */
    T rootMeanSquare()
    {
        return coreTimeDomainFeatures.rootMeanSquare(audioFrame);
    }
    
    /** Calculates the peak energy of the currently stored audio frame
     * @returns the peak energy value
     */
    T peakEnergy()
    {
        return coreTimeDomainFeatures.peakEnergy(audioFrame);
    }
    
    /** Calculates the zero crossing rate of the currently stored audio frame
     * @returns the zero crossing rate
     */
    T zeroCrossingRate()
    {
        return coreTimeDomainFeatures.zeroCrossingRate(audioFrame);
    }
    
    //=============== CORE FREQUENCY DOMAIN FEATURES ==============

    /** Calculates the spectral centroid from the magnitude spectrum 
     * @returns the spectral centroid 
     */
    T spectralCentroid()
    {
        return coreFrequencyDomainFeatures.spectralCentroid(magnitudeSpectrum);
    }
    
    /** Calculates the spectral crest
     * @returns the spectral crest
     */
    T spectralCrest()
    {
        return coreFrequencyDomainFeatures.spectralCrest(magnitudeSpectrum);
    }
    
    /** Calculates the spectral flatness from the magnitude spectrum
     * @returns the spectral flatness
     */
    T spectralFlatness()
    {
        return coreFrequencyDomainFeatures.spectralFlatness(magnitudeSpectrum);
    }
    
    //================= ONSET DETECTION FUNCTIONS =================
    
    /** Calculates the energy difference onset detection function sample for the magnitude spectrum frame
     * @returns the energy difference onset detection function sample
     */
    T energyDifference()
    {
        return onsetDetectionFunction.energyDifference(audioFrame);
    }
    
    /** Calculates the spectral difference onset detection function sample for the magnitude spectrum frame
     * @returns the spectral difference onset detection function sample
     */
    T spectralDifference()
    {
        return onsetDetectionFunction.spectralDifference(magnitudeSpectrum);
    }

    /** Calculates the complex spectral difference onset detection function sample for the magnitude spectrum frame
     * @returns the complex spectral difference onset detection function sample
     */
    T spectralDifferenceHWR()
    {
        return onsetDetectionFunction.spectralDifferenceHWR(magnitudeSpectrum);
    }

    /** Calculates the complex spectral difference onset detection function sample for the magnitude spectrum frame
     * @returns the complex spectral difference onset detection function sample
     */
    T complexSpectralDifference()
    {
        return onsetDetectionFunction.complexSpectralDifference(fftReal,fftImag);
    }
    
    /** Calculates the high frequency content onset detection function sample for the magnitude spectrum frame
     * @returns the high frequency content onset detection function sample
     */
    T highFrequencyContent()
    {
        return onsetDetectionFunction.highFrequencyContent(magnitudeSpectrum);
    }
    
    //=========================== PITCH ============================
    
    /** Calculates monophonic pitch according to the Yin algorithm
     * @returns the pitch estimate for the audio frame
     */
    T pitchYin()
    {
        return yin.pitchYin(audioFrame);
    }
    
    //=========================== MFCCs =============================

    /** Calculates the Mel Frequency Spectrum
     * @returns the Mel spectrum as a vector
     */
    std::vector<T> melFrequencySpectrum()
    {
        return mfcc.melFrequencySpectrum(magnitudeSpectrum);
    }
    
    /** Calculates Mel Frequency Cepstral Coefficients
     * @returns the MFCCs as a vector
     */
    std::vector<T> melFrequencyCepstralCoefficients()
    {
        return mfcc.melFrequencyCepstralCoefficients(magnitudeSpectrum);
    }
    
    
private:
    
    //=======================================================================
    
    /** configure the FFT implementation given the audio frame size) */
    void configureFFT()
    {
        if (fftConfigured)
        {
            freeFFT();
        }
        
        
#ifdef USE_FFTW
        // ------------------------------------------------------
        // initialise the fft time and frequency domain audio frame arrays
        fftIn = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * frameSize);		// complex array to hold fft data
        fftOut = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * frameSize);	// complex array to hold fft data
        
        // FFT plan initialisation
        p = fftw_plan_dft_1d(frameSize, fftIn, fftOut, FFTW_FORWARD, FFTW_ESTIMATE);
#endif /* END USE_FFTW */
        
        
#ifdef USE_KISS_FFT
        // ------------------------------------------------------
        // initialise the fft time and frequency domain audio frame arrays
        fftIn = new kiss_fft_cpx[frameSize];
        fftOut = new kiss_fft_cpx[frameSize];
        cfg = kiss_fft_alloc(frameSize,0,0,0);
#endif /* END USE_KISS_FFT */
        
        fftConfigured = true;
    }
    
    /** Free all FFT-related data */
    void freeFFT()
    {
        
#ifdef USE_FFTW
        // destroy fft plan
        fftw_destroy_plan(p);
        
        fftw_free(fftIn);
        fftw_free(fftOut);
#endif
        
#ifdef USE_KISS_FFT
        // free the Kiss FFT configuration
        free(cfg);
        
        delete [] fftIn;
        delete [] fftOut;
#endif
        
    }
    
    
    /** perform the FFT on the current audio frame */
    void performFFT()
    {
#ifdef USE_FFTW
        // copy samples from audio frame
        for (int i = 0;i < frameSize;i++)
        {
            fftIn[i][0] = (double) audioFrame[i];
            fftIn[i][1] = (double) 0.0;
        }
        
        // perform the FFT
        fftw_execute(p);
        
        // store real and imaginary parts of FFT
        for (int i = 0;i < frameSize;i++)
        {
            fftReal[i] = (T) fftOut[i][0];
            fftImag[i] = (T) fftOut[i][1];
        }
#endif
        
#ifdef USE_KISS_FFT
        for (int i = 0;i < frameSize;i++)
        {
            fftIn[i].r = (double) audioFrame[i];
            fftIn[i].i = 0.0;
        }
        
        // execute kiss fft
        kiss_fft(cfg, fftIn, fftOut);
        
        // store real and imaginary parts of FFT
        for (int i = 0;i < frameSize;i++)
        {
            fftReal[i] = (T) fftOut[i].r;
            fftImag[i] = (T) fftOut[i].i;
        }
#endif
        
        
        
        // calculate the magnitude spectrum
        for (int i = 0;i < frameSize/2;i++)
        {
            magnitudeSpectrum[i] = sqrt((fftReal[i]*fftReal[i]) + (fftImag[i]*fftImag[i]));
        }

    }
    
    //=======================================================================
    
    #ifdef USE_FFTW
    fftw_plan p;                        /**< fftw plan */
	fftw_complex *fftIn;				/**< to hold complex fft values for input */
	fftw_complex *fftOut;               /**< to hold complex fft values for output */
    #endif
    
    #ifdef USE_KISS_FFT
    kiss_fft_cfg cfg;                   /**< Kiss FFT configuration */
    kiss_fft_cpx *fftIn;                /**< FFT input samples, in complex form */
    kiss_fft_cpx *fftOut;               /**< FFT output samples, in complex form */
    #endif
    
    int frameSize;                      /**< The audio frame size */
    
    std::vector<T> audioFrame;          /**< The current audio frame */
    std::vector<T> fftReal;             /**< The real part of the FFT for the current audio frame */
    std::vector<T> fftImag;             /**< The imaginary part of the FFT for the current audio frame */
    std::vector<T> magnitudeSpectrum;   /**< The magnitude spectrum of the current audio frame */
    
    bool fftConfigured;
    
    /** object to compute core time domain features */
    CoreTimeDomainFeatures<T> coreTimeDomainFeatures;
    
    /** object to compute core frequency domain features */
    CoreFrequencyDomainFeatures<T> coreFrequencyDomainFeatures;
    
    /** object to compute onset detection functions */
    OnsetDetectionFunction<T> onsetDetectionFunction;
    
    /** object to compute pitch estimates via the Yin algorithm */
    Yin<T> yin;
    
    /** object to compute MFCCs and mel-frequency specta */
    MFCC<T> mfcc;
};


#endif
