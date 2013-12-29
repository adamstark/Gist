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
Yin<T>::Yin()
{
    
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
int Yin<T>::getPeriodCandidate(std::vector<T> delta)
{
    int minPeriod = 30;
    int period;
    
    T thresh = 0.1;
    
    std::vector<int> candidates;
    
    T minVal = 100000;
    int minInd = 0;
    
    for (int i = minPeriod;i < (delta.size()-1);i++)
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
template class Yin<float>;
template class Yin<double>;