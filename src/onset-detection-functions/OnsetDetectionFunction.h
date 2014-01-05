//=======================================================================
/** @file OnsetDetectionFunction.h
 *  @brief Implementations of onset detection functions
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


#ifndef __GIST__ONSETDETECTIONFUNCTION__
#define __GIST__ONSETDETECTIONFUNCTION__

#include <vector>

/** template class for calculating onset detection functions
 * Instantiations of the class should be of either 'float' or 
 * 'double' types and no others */
template <class T>
class OnsetDetectionFunction
{
    
public:
    /** constructor */
    OnsetDetectionFunction(int frameSize);
    
    /** Sets the frame size of internal buffers. Assumes all magnitude
     * spectra are passed as the first half (i.e. not mirrored)
     * @param frameSize the frame size
     */
    void setFrameSize(int frameSize);
    
    //===========================================================
    /** calculates the spectral difference between the current magnitude
     * spectrum and the previous magnitude spectrum
     * @param magnitudeSpectrum a vector containing the magnitude spectrum
     * @returns the spectral difference
     */
    T spectralDifference(std::vector<T> magnitudeSpectrum);
    
    /** calculates the spectral difference between the current magnitude
     * spectrum and the previous magnitude spectrum
     * @param magnitudeSpectrum a pointer to an array containing the magnitude spectrum
     * @param numSamples the number of frequency elements in the array
     * @returns the spectral difference
     */
    T spectralDifference(T *magnitudeSpectrum,unsigned long numSamples);
    
    //===========================================================
    /** calculates the half wave rectified spectral difference between the 
     * current magnitude spectrum and the previous magnitude spectrum
     * @param magnitudeSpectrum a vector containing the magnitude spectrum
     * @returns the spectral difference
     */
    T spectralDifferenceHWR(std::vector<T> magnitudeSpectrum);
    
    /** calculates the half wave rectified spectral difference between the
     * current magnitude spectrum and the previous magnitude spectrum
     * @param magnitudeSpectrum a pointer to an array containing the magnitude spectrum
     * @param numSamples the number of frequency elements in the array
     * @returns the spectral difference
     */
    T spectralDifferenceHWR(T *magnitudeSpectrum,unsigned long numSamples);
    
private:
    
    /** a vector containing the previous magnitude spectrum passed to the
     last spectral difference call */
    std::vector<T> prevMagnitudeSpectrum_spectralDifference;
    
    /** a vector containing the previous magnitude spectrum passed to the
     last spectral difference (half wave rectified) call */
    std::vector<T> prevMagnitudeSpectrum_spectralDifferenceHWR;
    
};

#endif