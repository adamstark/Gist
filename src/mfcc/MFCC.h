//=======================================================================
/** @file MFCC.h
 *  @brief Calculates Mel Frequency Cepstral Coefficients
 *  @author Adam Stark
 *  @copyright Copyright (C) 2014  Adam Stark
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

#ifndef __GIST__MFCC__
#define __GIST__MFCC__

#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>

/** Template class for calculating Mel Frequency Cepstral Coefficients
 * Instantiations of the class should be of either 'float' or
 * 'double' types and no others */
template <class T>
class MFCC
{
public:
    /** Constructor */
    MFCC(int frameSize_,int samplingFrequency_);
    
    /** Set the number of coefficients to calculate
     * @param numCoefficients_ the number of coefficients to calculate 
     */
    void setNumCoefficients(int numCoefficients_);
    
    /** Set the frame size - N.B. this will be twice the length of the magnitude spectrum passed to calculateMFCC()
     * @param frameSize_ the frame size
     */
    void setFrameSize(int frameSize_);
    
    /** Set the sampling frequency
     * @param samplingFrequency_ the sampling frequency in hz
     */
    void setSamplingFrequency(int samplingFrequency_);
    
    /** Calculates the Mel Frequency Cepstral Coefficients from the magnitude spectrum of a signal. Note that
     * the magnitude spectrum passed to the function is not the full mirrored magnitude spectrum, but only the
     * first half. The frame size passed to the constructor should be twice the length of the magnitude spectrum.
     * @param magnitudeSpectrum the magnitude spectrum in vector format
     * @returns a vector containing the MFCCs
     */
    std::vector<T> melFrequencyCepstralCoefficients(std::vector<T> magnitudeSpectrum);
    
    /** Calculates the magnitude spectrum on a Mel scale
     * @returns a vector containing the Mel spectrum
     */
    std::vector<T> melFrequencySpectrum(std::vector<T> magnitudeSpectrum);
    
private:
    /** Initialises the parts of the algorithm dependent on frame size, sampling frequency
     * and the number of coefficients
     */
    void initialise();
    
    /** Calculates the discrete cosine transform (version 2) of an input signal 
     * @param inputSignal a vector containing the input signal
     * @returns a vector containing the DCT of the input signal
     */
    std::vector<T> discreteCosineTransform(std::vector<T> inputSignal);
    
    /** Calculates the triangular filters used in the algorithm. These will be different depending
     * upon the frame size, sampling frequency and number of coefficients and so should be re-calculated
     * should any of those parameters change.
     */
    void calculateMelFilterBank();
    
    /** Calculates mel from frequency
     * @param frequency the frequency in Hz
     * @returns the equivalent mel value
     */
    T frequencyToMel(T frequency);
    
    /** the sampling frequency in Hz */
    int samplingFrequency;
    
    /** the number of MFCCs to calculate */
    int numCoefficents;
    
    /** the audio frame size */
    int frameSize;
    
    /** the magnitude spectrum size (this will be half the frame size) */
    int magnitudeSpectrumSize;
    
    /** the minimum frequency to be used in the calculation of MFCCs */
    T minFrequency;
    
    /** the maximum frequency to be used in the calculation of MFCCs */
    T maxFrequency;
    
    /** a vector of vectors to hold the values of the triangular filters */
    std::vector<std::vector<T>> filterBank;
    
};

#endif /* defined(__GIST__MFCC__) */
