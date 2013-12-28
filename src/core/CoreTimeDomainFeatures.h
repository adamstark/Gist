


#ifndef __CORETIMEDOMAINFEATURES__
#define __CORETIMEDOMAINFEATURES__

class CoreTimeDomainFeatures
{
    
public:
    CoreTimeDomainFeatures();
    
    float RMS(std::vector<float> buffer);
    
    float peakEnergy(std::vector<float> buffer);
    
    float zeroCrossingRate(std::vector<float> buffer);
    
    float standardDeviation(std::vector<float> buffer);
};

#endif