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
T power (int value, int exponent)
{
    int result = 1;
    
    for (int i = 0;i < exponent;i++)
    {
        result *= value;
    }
    
    return (T) result;
}

//===========================================================
template <class T>
T spectralStatistic (std::vector<T> magnitudeSpectrum, int i)
{
    T sumVal1 = 0;
    T sumVal2 = 0;
    
    for (int k = 0; k < magnitudeSpectrum.size(); k++)
    {
        sumVal1 += power<T> (k, i) * magnitudeSpectrum[k];
        sumVal2 += magnitudeSpectrum[k];
    }
    
    if (sumVal2 == 0)
    {
        return 0;
    }
    else
    {
        return sumVal1 / sumVal2;
    }
}

//===========================================================
template <class T>
CoreFrequencyDomainFeatures<T>::CoreFrequencyDomainFeatures()
{
}

//===========================================================
template <class T>
T CoreFrequencyDomainFeatures<T>::spectralCentroid (std::vector<T> magnitudeSpectrum)
{
    // to hold sum of amplitudes
    T sumAmplitudes = 0.0;

    // to hold sum of weighted amplitudes
    T sumWeightedAmplitudes = 0.0;

    // for each bin in the first half of the magnitude spectrum
    for (int i = 0; i < magnitudeSpectrum.size(); i++)
    {
        // sum amplitudes
        sumAmplitudes += magnitudeSpectrum[i];

        // sum amplitudes weighted by the bin number
        sumWeightedAmplitudes += magnitudeSpectrum[i] * i;
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
template <class T>
T CoreFrequencyDomainFeatures<T>::spectralFlatness (std::vector<T> magnitudeSpectrum)
{
    double sumVal = 0.0;
    double logSumVal = 0.0;
    double N = (double)magnitudeSpectrum.size();

    T flatness;

    for (int i = 0; i < magnitudeSpectrum.size(); i++)
    {
        // add one to stop zero values making it always zero
        double v = (double)(1 + magnitudeSpectrum[i]);

        sumVal += v;
        logSumVal += log (v);
    }

    sumVal = sumVal / N;
    logSumVal = logSumVal / N;

    if (sumVal > 0)
    {
        flatness = (T)(exp (logSumVal) / sumVal);
    }
    else
    {
        flatness = 0.0;
    }

    return flatness;
}

//===========================================================
template <class T>
T CoreFrequencyDomainFeatures<T>::spectralCrest (std::vector<T> magnitudeSpectrum)
{
    T sumVal = 0.0;
    T maxVal = 0.0;
    T N = (T)magnitudeSpectrum.size();

    for (int i = 0; i < magnitudeSpectrum.size(); i++)
    {
        T v = magnitudeSpectrum[i] * magnitudeSpectrum[i];
        sumVal += v;

        if (v > maxVal)
        {
            maxVal = v;
        }
    }

    T spectralCrest;

    if (sumVal > 0)
    {
        T meanVal = sumVal / N;

        spectralCrest = maxVal / meanVal;
    }
    else
    {
        // this is a ratio so we return 1.0 if the buffer is just zeros
        spectralCrest = 1.0;
    }

    return spectralCrest;
}

//===========================================================
template <class T>
T CoreFrequencyDomainFeatures<T>::spectralRolloff (std::vector<T> magnitudeSpectrum, T percentile)
{
    T sumOfMagnitudeSpectrum = std::accumulate (magnitudeSpectrum.begin(), magnitudeSpectrum.end(), 0);
    T threshold = sumOfMagnitudeSpectrum * percentile;
    
    T cumulativeSum = 0;
    int index = 0;
    
    for (int i = 0; i < magnitudeSpectrum.size();i++)
    {
        cumulativeSum += magnitudeSpectrum[i];
        
        if (cumulativeSum > threshold)
        {
            index = i;
            break;
        }
    }
    
    T spectralRolloff = ((T)index) / ((T)magnitudeSpectrum.size());
    
    return spectralRolloff;
}

//===========================================================
template <class T>
T CoreFrequencyDomainFeatures<T>::spectralSpread (std::vector<T> magnitiudeSpectrum)
{
    T u1 = spectralStatistic (magnitiudeSpectrum, 1);
    T u2 = spectralStatistic (magnitiudeSpectrum, 2);
    
    T result = u2 - u1 * u1;
    
    if (result >= 0)
    {
        return sqrt (result);
    }
    else
    {
        return 0;
    }
}

//===========================================================
template <class T>
T CoreFrequencyDomainFeatures<T>::spectralSkewness (std::vector<T> magnitiudeSpectrum)
{
    T u1 = spectralStatistic (magnitiudeSpectrum, 1);
    T u2 = spectralStatistic (magnitiudeSpectrum, 2);
    T u3 = spectralStatistic (magnitiudeSpectrum, 3);
    T ss = spectralSpread (magnitiudeSpectrum);
    
    T result = (2. * (u1 * u1 * u1)) - 3 * u1 * u2 + u3;
    result = result / (ss * ss * ss);
    
    return result;
}

//===========================================================
template <class T>
T CoreFrequencyDomainFeatures<T>::spectralKurtosis (std::vector<T> magnitudeSpectrum)
{
    // https://en.wikipedia.org/wiki/Kurtosis#Sample_kurtosis
    
    T sumOfMagnitudeSpectrum = std::accumulate (magnitudeSpectrum.begin(), magnitudeSpectrum.end(), 0);
    
    T mean = sumOfMagnitudeSpectrum / (T)magnitudeSpectrum.size();
    
    T moment2 = 0;
    T moment4 = 0;
    
    for (int i = 0; i < magnitudeSpectrum.size(); i++)
    {
        T difference = magnitudeSpectrum[i] - mean;
        T squaredDifference = difference*difference;
        
        moment2 += squaredDifference;
        moment4 += squaredDifference*squaredDifference;
    }
    
    moment2 = moment2 / (T)magnitudeSpectrum.size();
    moment4 = moment4 / (T)magnitudeSpectrum.size();
        
    if (moment2 == 0)
    {
        return -3.;
    }
    else
    {
        return (moment4 / (moment2*moment2)) - 3.;
    }
}

//===========================================================
template <class T>
T CoreFrequencyDomainFeatures<T>::spectralDecrease (std::vector<T> magnitudeSpectrum)
{
    T sumVal1 = 0;
    T sumVal2 = 0;
    
    for (int k = 1; k < magnitudeSpectrum.size(); k++)
    {
        T difference = magnitudeSpectrum[k] - magnitudeSpectrum[0];
        
        sumVal1 += difference / (T)k;
        sumVal2 += magnitudeSpectrum[k];
    }
    
    if (sumVal2 == 0)
    {
        return 0;
    }
    else
    {
        return sumVal1 / sumVal2;
    }
}

//===========================================================
template class CoreFrequencyDomainFeatures<float>;
template class CoreFrequencyDomainFeatures<double>;
