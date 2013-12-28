#ifndef __ONSETDETECTIONFUNCTION__
#define __ONSETDETECTIONFUNCTION__

#include <vector>

class OnsetDetectionFunction
{
    
public:
    OnsetDetectionFunction();
    
    float spectralDifference(std::vector<float> magnitudeSpectrum);
    
private:
    
    std::vector<float> prevMagnitudeSpectrum;
    
};

#endif