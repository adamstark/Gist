#include "CoreFrequencyDomainFeatures.h"

//===========================================================
CoreFrequencyDomainFeatures::CoreFrequencyDomainFeatures()
{
    
}

//===========================================================
float CoreFrequencyDomainFeatures::spectralCentroid(std::vector<float> magnitudeSpectrum)
{
    // to hold sum of amplitudes
    float sumAmplitudes = 0.0;
    
    // to hold sum of weighted amplitudes
    float sumWeightedAmplitudes = 0.0;
    
    // for each bin in the first half of the magnitude spectrum
    for (int i = 0;i < magnitudeSpectrum.size()/2;i++)
    {
        // sum amplitudes
        sumAmplitudes += magnitudeSpectrum[i];
        
        // sum amplitudes weighted by the bin number
        sumWeightedAmplitudes += magnitudeSpectrum[i]*i;
    }
    
    // the spectral centroid is the sum of weighted amplitudes divided by the sum of amplitdues
    return sumWeightedAmplitudes / sumAmplitudes;
}