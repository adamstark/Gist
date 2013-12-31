#ifndef ONSET_DETECTION_FUNCTION_TESTS
#define ONSET_DETECTION_FUNCTION_TESTS

#include "../../src/Gist.h"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

//=============================================================
//=================== SPECTRAL DIFFERENCE =====================
//=============================================================
BOOST_AUTO_TEST_SUITE(SpectralDifference)

// ------------------------------------------------------------
// 1. Check that a buffer of zeros returns zero on two occasions
BOOST_AUTO_TEST_CASE(Zero_Test)
{
    int frameSize = 512;
    
    OnsetDetectionFunction<float> odf(frameSize);
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 0;
    }
    
    // first time
    float r = odf.spectralDifference(testSpectrum);

    BOOST_CHECK_EQUAL(r,0);
    
    // second time
    r = odf.spectralDifference(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,0);
    
}

// ------------------------------------------------------------
// 2. Check that a buffer of ones returns the frame size the first time
// and zero the second time
BOOST_AUTO_TEST_CASE(Ones_Test)
{
    int frameSize = 512;
    
    OnsetDetectionFunction<float> odf(frameSize);
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 1;
    }
    
    // first time
    float r = odf.spectralDifference(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,frameSize);
    
    // second time
    r = odf.spectralDifference(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,0);
    
}

// ------------------------------------------------------------
// 3. Numerical Test
BOOST_AUTO_TEST_CASE(NumericalTest)
{
    int frameSize = 512;
    
    OnsetDetectionFunction<float> odf(frameSize);
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = i;
    }
    
    // first time
    float r = odf.spectralDifference(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,130816);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 1;
    }
    
    // second time
    r = odf.spectralDifference(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,130306);
    
}

BOOST_AUTO_TEST_SUITE_END()

//=============================================================
//========= SPECTRAL DIFFERENCE (HALF WAVE RECTIFIED) =========
//=============================================================
BOOST_AUTO_TEST_SUITE(SpectralDifferenceHWR)

// ------------------------------------------------------------
// 1. Check that a buffer of zeros returns zero on two occasions
BOOST_AUTO_TEST_CASE(Zero_Test)
{
    int frameSize = 512;
    
    OnsetDetectionFunction<float> odf(frameSize);
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 0;
    }
    
    // first time
    float r = odf.spectralDifferenceHWR(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,0);
    
    // second time
    r = odf.spectralDifferenceHWR(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,0);
    
}

// ------------------------------------------------------------
// 2. Check that a buffer of ones returns the frame size the first time
// and zero the second time
BOOST_AUTO_TEST_CASE(Ones_Test)
{
    int frameSize = 512;
    
    OnsetDetectionFunction<float> odf(frameSize);
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 1;
    }
    
    // first time
    float r = odf.spectralDifferenceHWR(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,frameSize);
    
    // second time
    r = odf.spectralDifferenceHWR(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,0);
    
}

// ------------------------------------------------------------
// 3. Numerical Test
BOOST_AUTO_TEST_CASE(NumericalTest)
{
    int frameSize = 512;
    
    OnsetDetectionFunction<float> odf(frameSize);
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = i;
    }
    
    // first time
    float r = odf.spectralDifferenceHWR(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,130816);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 0;
    }
    
    // second time
    r = odf.spectralDifferenceHWR(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,0);
    
}

BOOST_AUTO_TEST_SUITE_END()

#endif
