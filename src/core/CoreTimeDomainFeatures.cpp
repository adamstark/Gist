#include "CoreTimeDomainFeatures.h"


//===========================================================
CoreTimeDomainFeatures::CoreTimeDomainFeatures()
{
    

}

//===========================================================
float CoreTimeDomainFeatures::RMS(std::vector<float> buffer)
{
    // create variable to hold the sum
    float sum = 0;
    
    // sum the squared samples
    for (int i = 0;i < buffer.size();i++)
    {
        sum += pow(buffer[i],2);
    }
    
    // return the square root of the mean of squared samples
    return sqrt(sum / ((float) buffer.size()));
}

//===========================================================
float CoreTimeDomainFeatures::peakEnergy(std::vector<float> buffer)
{
    // create variable with very small value to hold the peak value
    float peak = -10000.0;
    
    // for each audio sample
    for (int i = 0;i < buffer.size();i++)
    {
        // store the absolute value of the sample
        float absSample = fabs(buffer[i]);
        
        // if the absolute value is larger than the peak
        if (absSample > peak)
        {
            // the peak takes on the sample value
            peak = absSample;
        }
    }
    
    // return the peak value
    return peak;
}


//===========================================================
float CoreTimeDomainFeatures::zeroCrossingRate(std::vector<float> buffer)
{
    // create a variable to hold the zero crossing rate
    float zcr;
    
    // for each audio sample, starting from the second one
    for (int i = 1;i < buffer.size();i++)
    {
        // initialise two booleans indicating whether or not
        // the current and previous sample are positive
        bool current = (buffer[i] > 0);
        bool previous = (buffer[i-1] > 0);
        
        // if the sign is different
        if (current != previous)
        {
            // add one to the zero crossing rate
            zcr = zcr + 1.0;
        }
    }
    
    // return the zero crossing rate
    return zcr;
}

//===========================================================
float CoreTimeDomainFeatures::standardDeviation(std::vector<float> buffer)
{
    if (buffer.size() > 0)
    {
        // create variable to hold the sum
        float sum = 0;
        float mean;
        float std;
        float N = (float) buffer.size();
        
        // sum the  samples
        for (int i = 0;i < buffer.size();i++)
        {
            sum += buffer[i];
        }
        
        mean = sum / N;
        
        sum = 0;
        for (int i = 0;i < buffer.size();i++)
        {
            sum += fabs(buffer[i]-mean);
        }
        
        std = sqrt(sum / N);
        
        return std;
    }
    else
    {
        return 0.0;
    }
}