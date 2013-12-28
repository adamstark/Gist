#include "PitchDetection.h"

//===========================================================
PitchDetection::PitchDetection()
{
    
}

//===========================================================
std::vector<float> PitchDetection::cumulativeMeanNormalisedDifferenceFunction(std::vector<float> frame)
{
    float cumulativeSum = 0.0;
    
    // create a new empty buffer
    //delta = np.zeros(frame.size/2)
    
    std::vector<float> delta;
    
    delta.resize(frame.size()/2);
    
    
    
    // for each time lag tau
    for (int tau = 0;tau < frame.size()/2;tau++)
    {
        //float sumVal = 0.0;
        delta[tau] = 0.0;
        
        // sum all squared differences for all samples up to half way through
        // the frame between the sample and the sample 'tau' samples away
        for (int j = 0;j < frame.size()/2;j++)
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