//=======================================================================
/** @file CoreFrequencyDomainFeatures.cpp
 *  @brief Implementations of common frequency domain audio features
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


#include "CoreFrequencyDomainFeatures.h"

//===========================================================
template <class T>
CoreFrequencyDomainFeatures<T>::CoreFrequencyDomainFeatures()
{
    
}

//===========================================================
template <class T>
T CoreFrequencyDomainFeatures<T>::spectralCentroid(std::vector<T> magnitudeSpectrum)
{
    // to hold sum of amplitudes
    T sumAmplitudes = 0.0;
    
    // to hold sum of weighted amplitudes
    T sumWeightedAmplitudes = 0.0;
    
    // for each bin in the first half of the magnitude spectrum
    for (int i = 0;i < magnitudeSpectrum.size();i++)
    {
        // sum amplitudes
        sumAmplitudes += magnitudeSpectrum[i];
        
        // sum amplitudes weighted by the bin number
        sumWeightedAmplitudes += magnitudeSpectrum[i]*i;
    }
    
    // if the sum of amplitudes is larger than zero (it should be if the buffer wasn't
    // all zeros)
    if (sumAmplitudes > 0)
    {
        // the spectral centroid is the sum of weighted amplitudes divided by the sum of amplitdues
        return sumWeightedAmplitudes / sumAmplitudes;
    }
    else // to be safe just return zero
    {
        return 0.0;
    }
}

//===========================================================
template class CoreFrequencyDomainFeatures<float>;
template class CoreFrequencyDomainFeatures<double>;