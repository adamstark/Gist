//=======================================================================
/** @file Yin.cpp
 *  @brief Implementation of the YIN pitch detection algorithm (de Cheveigné and Kawahara)
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

#include "Yin.h"

//===========================================================
template <class T>
Yin<T>::Yin(int samplingFrequency)
{
    setSamplingFrequency(samplingFrequency);
    
    setMaxFrequency(1500);
    
    prevPeriodEstimate = 1.0;
}

//===========================================================
template <class T>
void Yin<T>::setSamplingFrequency(int samplingFrequency)
{
    int oldFs = fs;
    
    fs = samplingFrequency;
    
    minPeriod = ((float) fs) / ((float) oldFs) * minPeriod;
}

//===========================================================
template <class T>
void Yin<T>::setMaxFrequency(T maxFreq)
{
    T minPeriodFloating;
    
    // if maxFrequency is zero or less than 200Hz, assume a bug
    // and set it to an arbitrary value fo 2000Hz
    if (maxFreq <= 200)
    {
        maxFreq = 2000.;
    }

    minPeriodFloating = ((T) fs) / maxFreq;
    
    minPeriod = (int) ceil(minPeriodFloating);
}

//===========================================================
template <class T>
T Yin<T>::pitchYin(std::vector<T> frame)
{
    return pitchYin(&frame[0], frame.size());
}

//===========================================================
template <class T>
T Yin<T>::pitchYin(T *frame,unsigned long numSamples)
{
    unsigned long period;
    T fPeriod;
    
    // steps 1, 2 and 3 of the Yin algorithm
    // get the difference function ("delta")
    std::vector<T> delta = cumulativeMeanNormalisedDifferenceFunction(frame,numSamples);
    
    // first, see if the previous period estimate has a minima
    long continuityPeriod = searchForOtherRecentMinima(delta);
    
    // if there is no minima at the previous period estimate
    if (continuityPeriod == -1)
    {
        // then estimate the period from the function
        period = getPeriodCandidate(delta);
    }
    else // if there was a minima at the previous period estimate
    {
        // go with that
        period = (unsigned long)continuityPeriod;
    }
    
    // CHECK - CAN THE PERIOD ACCESS -1 AND ARRAY[MAX+1]?
    // WELL, NOT -1, BECAUSE IT IS AN UNSIGNED LONG
    // BUT WHAT IF CONTINUITY PERIOD COMES OUT WACKY?
    fPeriod = parabolicInterpolation(period,delta[period-1],delta[period],delta[period+1]);
    
    // store the previous period estimate for later
    prevPeriodEstimate = fPeriod;
    
    return periodToPitch(fPeriod);
}

//===========================================================
template <class T>
std::vector<T> Yin<T>::cumulativeMeanNormalisedDifferenceFunction(T *frame,unsigned long numSamples)
{
    T cumulativeSum = 0.0;
    
    std::vector<T> delta;
    
    delta.resize(numSamples/2);

    // for each time lag tau
    for (int tau = 0;tau < numSamples/2;tau++)
    {
        delta[tau] = 0.0;
        
        // sum all squared differences for all samples up to half way through
        // the frame between the sample and the sample 'tau' samples away
        for (int j = 0;j < numSamples/2;j++)
        {
            delta[tau] = delta[tau] + pow(frame[j] - frame[j+tau],2);
        }
        
        // calculate the cumulative sum of tau values to date
        cumulativeSum = cumulativeSum + delta[tau];
        
        if (cumulativeSum > 0)
        {
            delta[tau] = delta[tau]*tau / cumulativeSum;
        }
    }
    
    // set the first element to zero
    delta[0] = 1.;
    
    return delta;
}

//===========================================================
template <class T>
unsigned long Yin<T>::getPeriodCandidate(std::vector<T> delta)
{
    unsigned long minPeriod = 30;
    unsigned long period;
    
    T thresh = 0.1;
    
    std::vector<unsigned long> candidates;
    
    T minVal = 100000;
    unsigned long minInd = 0;
    
    for (unsigned long i = minPeriod;i < (delta.size()-1);i++)
    {
        if (delta[i] < minVal)
        {
            minVal = delta[i];
            minInd = i;
        }
        
        if (delta[i] < thresh)
        {
            if ((delta[i] < delta[i-1]) && (delta[i] < delta[i+1]))
            {
                candidates.push_back(i);
            }
        }
    }
    
    if (candidates.size() == 0)
    {
        period = minInd;
    }
    else
    {
        period = candidates[0];
    }
    
    return period;
}

//===========================================================
template <class T>
T Yin<T>::parabolicInterpolation(unsigned long period,T y1,T y2,T y3)
{
    // if all elements are the same, our interpolation algorithm
    // will end up with a divide-by-zero, so just return the original
    // period without interpolation
    if ((y3 == y2) && (y2 == y1))
    {
        return (T) period;
    }
    else
    {
        T newPeriod = ((T)period) + (y3-y1) / (2. * (2* y2-y3-y1));
    
        return newPeriod;
    }
}

//===========================================================
template <class T>
long Yin<T>::searchForOtherRecentMinima(std::vector<T> delta)
{
    long newMinima = -1;
    
    long prevEst;
    
    prevEst = (long) round(prevPeriodEstimate);
    
    for (long i = prevEst-1;i <= prevEst+1;i++)
    {
        if ((i > 0) && (i < delta.size()-1))
        {
            if ((delta[i] < delta[i-1]) && (delta[i] < delta[i+1]))
            {
                newMinima = i;
            }
        }
    }
    
    return newMinima;
    
}

//===========================================================
template <class T>
T Yin<T>::periodToPitch(T period)
{
    return ((T) fs) / period;
}

//===========================================================
template class Yin<float>;
template class Yin<double>;