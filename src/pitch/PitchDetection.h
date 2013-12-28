#ifndef __PITCHDETECTION__
#define __PITCHDETECTION__

#include <vector>
#include <math.h>

class PitchDetection
{
    
public:
    PitchDetection();
    
    float pitchYin(std::vector<float> buffer)
    {
        return 0.0;
    }
    
    std::vector<float> cumulativeMeanNormalisedDifferenceFunction(std::vector<float> frame);
};

#endif