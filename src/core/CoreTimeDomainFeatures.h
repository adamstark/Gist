


#ifndef __CORETIMEDOMAINFEATURES__
#define __CORETIMEDOMAINFEATURES__

#include <vector>
#include <math.h>

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