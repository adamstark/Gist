//=======================================================================
/** @file Yin.h
 *  @brief Implementation of the YIN pitch detection algorithm (de Cheveigné and Kawahara,2002)
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

#ifndef __GIST__YIN__
#define __GIST__YIN__

#include <vector>
#include <math.h>

template <class T>
class Yin
{
    
public:
    Yin(int samplingFrequency);
    
    void setSamplingFrequency(int samplingFrequency);
    
    void setMaxFrequency(T maxFreq);
    
    T getMaxFrequency()
    {
        return ((T) fs) / ((T) minPeriod);
    }
    
    T pitchYin(std::vector<T> frame);
    
    T pitchYin(T *frame,unsigned long numSamples);
    
private:
    
    T periodToPitch(T period);

    long searchForOtherRecentMinima(std::vector<T> delta);
    
    T parabolicInterpolation(unsigned long period,T y1,T y2,T y3);
    
    unsigned long getPeriodCandidate(std::vector<T> delta);
    
    std::vector<T> cumulativeMeanNormalisedDifferenceFunction(T *frame,unsigned long numSamples);
    
    T prevPeriodEstimate;
    
    int fs;
    
    int minPeriod;
};

#endif
