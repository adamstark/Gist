//=======================================================================
/** @file gist.h
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

#define GIST_VERSION "0.1.0"

// core
#include "core/CoreTimeDomainFeatures.h"
#include "core/CoreFrequencyDomainFeatures.h"

// onset detection functions
#include "onset-detection-functions/OnsetDetectionFunction.h"

// pitch detection
#include "pitch/Yin.h"

// fft
#include "fftw3.h"

template <class T>
class Gist
{
public:
    
    Gist(int frameSize_,int sampleRate_) : yin(sampleRate_), onsetDetectionFunction(frameSize_), fftConfigured(false)
    {
        setAudioFrameSize(frameSize_);
    }
    
    ~Gist()
    {
        if (fftConfigured)
        {
            freeFFT();
        }
    }

    void setAudioFrameSize(int frameSize_)
    {
        frameSize = frameSize_;

        audioFrame.resize(frameSize);
        fftReal.resize(frameSize);
        fftImag.resize(frameSize);
        magnitudeSpectrum.resize(frameSize/2);
        
        configureFFT();
        
        onsetDetectionFunction.setFrameSize(frameSize);
    }
    
    void processAudioFrame(std::vector<T> audioFrame_)
    {
        audioFrame = audioFrame_;
        
        performFFT();
    }
    
    void processAudioFrame(T *buffer,unsigned long numSamples)
    {
        audioFrame.assign(buffer,buffer + numSamples);
        
        performFFT();
    }
    
    /** @returns the current magnitude spectrum */
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
    
    //================= ONSET DETECTION FUNCTIONS =================
    
    T spectralDifference()
    {
        return onsetDetectionFunction.spectralDifference(magnitudeSpectrum);
    }
    
    T spectralDifferenceHWR()
    {
        return onsetDetectionFunction.spectralDifferenceHWR(magnitudeSpectrum);
    }
    
    //=========================== PITCH ============================
    
    /** Calculates monophonic pitch according to the Yin algorithm
     * @returns the pitch estimate for the audio frame
     */
    T pitchYin()
    {
        return yin.pitchYin(audioFrame);
    }

    
private:
    
    /** configure the FFT implementation given the audio frame size) */
    void configureFFT()
    {
        if (fftConfigured)
        {
            freeFFT();
        }
        
        // initialise the fft time and frequency domain audio frame arrays
        fftIn = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * frameSize);		// complex array to hold fft data
        fftOut = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * frameSize);	// complex array to hold fft data
        
        // FFT plan initialisation
        p = fftw_plan_dft_1d(frameSize, fftIn, fftOut, FFTW_FORWARD, FFTW_ESTIMATE);
        
        fftConfigured = true;
    }
    
    void freeFFT()
    {
        // destroy fft plan
        fftw_destroy_plan(p);
        
        fftw_free(fftIn);
        fftw_free(fftOut);
    }
    
    
    /** perform the FFT on the current audio frame */
    void performFFT()
    {
        // copy samples from audio frame
        for (int i = 0;i < frameSize;i++)
        {
            fftIn[i][0] = (double) audioFrame[i];
            fftIn[i][0] = (double) 0.0;
        }
        
        // perform the FFT
        fftw_execute(p);
        
        // store real and imaginary parts of FFT
        for (int i = 0;i < frameSize;i++)
        {
            fftReal[i] = (T) fftOut[i][0];
            fftImag[i] = (T) fftOut[i][0];
        }

        // calculate the magnitude spectrum
        for (int i = 0;i < frameSize/2;i++)
        {
            magnitudeSpectrum[i] = sqrt(pow(fftReal[i],2) + pow(fftImag[i],2));
        }

    }
    
    fftw_plan p;                        /**< fftw plan */
	fftw_complex *fftIn;				/**< to hold complex fft values for input */
	fftw_complex *fftOut;               /**< to hold complex fft values for output */
    
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
};


#endif
