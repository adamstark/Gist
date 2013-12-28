#include "OnsetDetectionFunction.h"

//===========================================================
OnsetDetectionFunction::OnsetDetectionFunction()
{
    
}

//===========================================================
float OnsetDetectionFunction::spectralDifference(std::vector<float> magnitudeSpectrum)
{
    float sum = 0;	// initialise sum to zero
    
    for (int i = 0;i < magnitudeSpectrum.size();i++)
    {
        // calculate difference
        float diff = magnitudeSpectrum[i] - prevMagnitudeSpectrum[i];
        
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