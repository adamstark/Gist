//=======================================================================
/** @file MFCC.cpp
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

#include "MFCC.h"

//==================================================================
template <class T>
MFCC<T>::MFCC(int frameSize_,int samplingFrequency_)
{
    numCoefficents = 13;
    frameSize = frameSize_;
    samplingFrequency = samplingFrequency_;
    
    initialise();
}

//==================================================================
template <class T>
void MFCC<T>::setNumCoefficients(int numCoefficients_)
{
    numCoefficents = numCoefficients_;
    
    initialise();
}

//==================================================================
template <class T>
void MFCC<T>::setFrameSize(int frameSize_)
{
    frameSize = frameSize_;
    
    initialise();
}

//==================================================================
template <class T>
void MFCC<T>::setSamplingFrequency(int samplingFrequency_)
{
    samplingFrequency = samplingFrequency_;
    
    initialise();
}

//==================================================================
template <class T>
std::vector<T> MFCC<T>::melFrequencyCepstralCoefficients(std::vector<T> magnitudeSpectrum)
{
    std::vector<T> melSpec;
    
    melSpec = melFrequencySpectrum(magnitudeSpectrum);
    
    for (int i = 0;i < melSpec.size();i++)
    {
        melSpec[i] = log(melSpec[i]);
    }
    
    return discreteCosineTransform(melSpec);
}

//==================================================================
template <class T>
std::vector<T> MFCC<T>::melFrequencySpectrum(std::vector<T> magnitudeSpectrum)
{
    std::vector<T> filteredSpectrum;
    
    for (int i = 0;i < numCoefficents;i++)
    {
        double coeff = 0;
        
        for (int j = 0;j < magnitudeSpectrum.size();j++)
        {
            coeff += (T) ((magnitudeSpectrum[j]*magnitudeSpectrum[j])*filterBank[i][j]);
        }
        
        filteredSpectrum.push_back(coeff);
    }
    
    return filteredSpectrum;
}

//==================================================================
template <class T>
void MFCC<T>::initialise()
{
    magnitudeSpectrumSize = frameSize/2;
    minFrequency = 0;
    maxFrequency = samplingFrequency/2;
    
    calculateMelFilterBank();
}



//==================================================================
template <class T>
std::vector<T> MFCC<T>::discreteCosineTransform(std::vector<T> inputSignal)
{
    std::vector<T> outputSignal(inputSignal.size());
    
    T N = (T) inputSignal.size();
    T piOverN = M_PI / N;
    
    for (int k = 0;k < outputSignal.size();k++)
    {
        T sum = 0;
        T kVal = (T) k;
        
        for (int n = 0;n < inputSignal.size();n++)
        {
            T tmp = piOverN * (((T)n)+0.5) * kVal;
            
            sum += inputSignal[n]*cos(tmp);
        }
        
        outputSignal[k] = (T) (2*sum);
    }
    
    return outputSignal;
}



//==================================================================
template <class T>
void MFCC<T>::calculateMelFilterBank()
{
    int maxMel = floor(frequencyToMel(maxFrequency));
    int minMel = floor(frequencyToMel(minFrequency));
    
    filterBank.resize(numCoefficents);
    
    for (int i = 0;i < numCoefficents;i++)
    {
        filterBank[i].resize(magnitudeSpectrumSize);
        
        for (int j = 0;j < magnitudeSpectrumSize;j++)
        {
            filterBank[i][j] = 0.0;
        }
    }
    
    std::vector<int> centreIndices;
    
    for (int i = 0;i < numCoefficents + 2;i++)
    {
        double f = i * (maxMel - minMel) / (numCoefficents + 1) + minMel;
        
        double tmp = log(1 + 1000.0 / 700.0) / 1000.0;
        tmp = (exp(f * tmp) - 1) / 22050;
        
        tmp = 0.5 + 700 * ((double)magnitudeSpectrumSize) * tmp;
        
        tmp = floor(tmp);
        
        int centreIndex = (int) tmp;
        
        centreIndices.push_back(centreIndex);
    }
    
    for (int i = 0;i < numCoefficents;i++)
    {
        int filterBeginIndex = centreIndices[i];
        int filterCenterIndex = centreIndices[i+1];
        int filterEndIndex = centreIndices[i+2];
        
        T triangleRangeUp = (T)(filterCenterIndex - filterBeginIndex);
        T triangleRangeDown = (T)(filterEndIndex - filterCenterIndex);
        
        // upward slope
        for (int k = filterBeginIndex;k < filterCenterIndex;k++)
        {
            filterBank[i][k] = ((T)(k-filterBeginIndex)) / triangleRangeUp;
        }
        
        // downwards slope
        for (int k = filterCenterIndex;k < filterEndIndex;k++)
        {
            filterBank[i][k] = ((T)(filterEndIndex - k)) / triangleRangeDown;   
        }
    }
    
}

//==================================================================
template <class T>
T MFCC<T>::frequencyToMel(T frequency)
{
    return int(1127) * log(1 + (frequency / 700.0));
}


//===========================================================
template class MFCC<float>;
template class MFCC<double>;