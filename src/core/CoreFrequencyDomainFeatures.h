


#ifndef __COREFREQUENCYDOMAINFEATURES__
#define __COREFREQUENCYDOMAINFEATURES__

#include <vector>
#include <math.h>

class CoreFrequencyDomainFeatures
{
    
public:
    CoreFrequencyDomainFeatures();
    
    float spectralCentroid(std::vector<float> magnitudeSpectrum);

};

#endif