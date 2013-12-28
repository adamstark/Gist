//=======================================================================
/** @file OnsetDetectionFunction.cpp
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

#include "OnsetDetectionFunction.h"

//===========================================================
template <class T>
OnsetDetectionFunction<T>::OnsetDetectionFunction(int frameSize)
{
    // initialise buffers with the frame size
    setFrameSize(frameSize);
}

//===========================================================
template <class T>
void OnsetDetectionFunction<T>::setFrameSize(int frameSize)
{
    // resize the prev magnitude spectrum vector
    prevMagnitudeSpectrum.resize(frameSize);
    
    // fill it with zeros
    for (int i = 0;i < prevMagnitudeSpectrum.size();i++)
    {
        prevMagnitudeSpectrum[i] = 0.0;
    }
}

//===========================================================
template <class T>
T OnsetDetectionFunction<T>::spectralDifference(std::vector<T> magnitudeSpectrum)
{
    T sum = 0;	// initialise sum to zero
    
    for (int i = 0;i < magnitudeSpectrum.size();i++)
    {
        // calculate difference
        T diff = magnitudeSpectrum[i] - prevMagnitudeSpectrum[i];
        
        // ensure all difference values are positive
        if (diff < 0)
        {
            diff = diff*-1;
        }
        
        // add difference to sum
        sum = sum+diff;
        
        prevMagnitudeSpectrum[i] = magnitudeSpectrum[i];
    }
    
    return sum;
}

//===========================================================
template <class T>
T OnsetDetectionFunction<T>::spectralDifferenceHWR(std::vector<T> magnitudeSpectrum)
{
    T sum = 0;	// initialise sum to zero
    
    for (int i = 0;i < magnitudeSpectrum.size();i++)
    {
        // calculate difference
        T diff = magnitudeSpectrum[i] - prevMagnitudeSpectrum[i];
        
        // only for positive changes
        if (diff > 0)
        {
            // add difference to sum
            sum = sum+diff;
        }
        prevMagnitudeSpectrum[i] = magnitudeSpectrum[i];
    }
    
    return sum;
}


//===========================================================
template class OnsetDetectionFunction<float>;
template class OnsetDetectionFunction<double>;