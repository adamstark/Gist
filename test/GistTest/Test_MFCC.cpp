#ifndef MFCC_TESTS
#define MFCC_TESTS

#include "../../src/Gist.h"
#include "test-signals/Test_Signals.h"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

//=============================================================
//========================== MFCC =============================
//=============================================================
BOOST_AUTO_TEST_SUITE(MFCC_test)

// ------------------------------------------------------------
// 1. CHECK EXAMPLE MAGNITUDE SPECTRUM WITH KNOWN RESULT
BOOST_AUTO_TEST_CASE(ExampleMagnitudeSpectrumTest)
{
    MFCC<float> mfcc(512,44100);
    
    mfcc.setNumCoefficients(13);
    
    std::vector<float> magnitudeSpecV(256);
    
    for (int i = 0;i < 256;i++)
    {
        magnitudeSpecV[i] = magnitudeSpectrum[i];
    }
    
    std::vector<float> r = mfcc.melFrequencyCepstralCoefficients(magnitudeSpecV);
    
    for (int i = 0;i < r.size();i++)
    {
        BOOST_CHECK_CLOSE(r[i],mfccTest1_result[i],0.01);
    }
}


BOOST_AUTO_TEST_SUITE_END()

#endif
