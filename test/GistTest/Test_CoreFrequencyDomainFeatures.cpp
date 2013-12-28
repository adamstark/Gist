#ifndef CORE_FREQ_DOMAIN_FEATURES_TESTS
#define CORE_FREQ_DOMAIN_FEATURES_TESTS

#include "../../src/gist.h"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

//=============================================================
//==================== SPECTRAL CENTROID ======================
//=============================================================
BOOST_AUTO_TEST_SUITE(SpectralCentroid)

// ------------------------------------------------------------
// 1. Check that a buffer of zeros returns zero
BOOST_AUTO_TEST_CASE(Zero_Test)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 0;
    }
    
    float r = fdf.spectralCentroid(testSpectrum);

    BOOST_CHECK_EQUAL(r,0);
    
}

// ------------------------------------------------------------
// 2. Check that an even sized buffer of ones returns the mean of the middle two elements
BOOST_AUTO_TEST_CASE(Ones_Test)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 1;
    }
    
    float r = fdf.spectralCentroid(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,255.5);
    
}

// ------------------------------------------------------------
// 3. Numeric Example
BOOST_AUTO_TEST_CASE(Numeric1)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum(6);
    
    testSpectrum[0] = 0;
    testSpectrum[1] = 4.2;
    testSpectrum[2] = 2;
    testSpectrum[3] = 6.5;
    testSpectrum[4] = 7;
    testSpectrum[5] = 8;
    
    
    float r = fdf.spectralCentroid(testSpectrum);
    
    BOOST_CHECK_CLOSE(r,3.4548736462093865,0.001);
    
}

BOOST_AUTO_TEST_SUITE_END()

#endif
