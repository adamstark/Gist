#ifndef CORE_FREQ_DOMAIN_FEATURES_TESTS
#define CORE_FREQ_DOMAIN_FEATURES_TESTS

#include "../../src/Gist.h"

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

//=============================================================
//==================== SPECTRAL FLATNESS ======================
//=============================================================
BOOST_AUTO_TEST_SUITE(SpectralFlatness)

// ------------------------------------------------------------
// 1. Check that a buffer of ones returns 1
BOOST_AUTO_TEST_CASE(Ones_Test)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 1;
    }
    
    float r = fdf.spectralFlatness(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,1);
    
}

// ------------------------------------------------------------
// 2. Check that a buffer of twos returns 1
BOOST_AUTO_TEST_CASE(Twos_Test)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 2.0;
    }
    
    float r = fdf.spectralFlatness(testSpectrum);
    
    BOOST_CHECK_CLOSE(r,1,0.001);
    
}

// ------------------------------------------------------------
// 3. Check that a buffer of alternate twos and zeros returns correct value
BOOST_AUTO_TEST_CASE(AlternateTest)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        if ((i % 2) == 0)
        {
            testSpectrum[i] = 2.0;
        }
        else
        {
            testSpectrum[i] = 0.0;
        }
    }
    
    float r = fdf.spectralFlatness(testSpectrum);
    
    BOOST_CHECK_CLOSE(r, 0.866025,0.001);
    
}

BOOST_AUTO_TEST_SUITE_END()

//=============================================================
//===================== SPECTRAL CREST ========================
//=============================================================
BOOST_AUTO_TEST_SUITE(SpectralCrest)

// ------------------------------------------------------------
// 1. Check that a buffer of ones returns 1
BOOST_AUTO_TEST_CASE(Ones_Test)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 1;
    }
    
    float r = fdf.spectralCrest(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,1.0);
    
}

// ------------------------------------------------------------
// 2. Check that a buffer of zeros returns 1
BOOST_AUTO_TEST_CASE(Zeros_Test)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 0;
    }
    
    float r = fdf.spectralCrest(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,1.0);
    
}

// ------------------------------------------------------------
// 3. Check that alternate ones and zeros produces 2.0
BOOST_AUTO_TEST_CASE(AlternateTest)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        if ((i % 2) == 0)
        {
            testSpectrum[i] = 1;
        }
        else
        {
            testSpectrum[i] = 0.0;
        }
    }
    
    float r = fdf.spectralCrest(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,2.0);
    
}

// ------------------------------------------------------------
// 4. Check that a delta every four elements returns 4
BOOST_AUTO_TEST_CASE(EveryFour)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum(512);
    
    for (int i = 0;i < 512;i++)
    {
        if ((i % 4) == 0)
        {
            testSpectrum[i] = 1;
        }
        else
        {
            testSpectrum[i] = 0.0;
        }
    }
    
    float r = fdf.spectralCrest(testSpectrum);
    
    BOOST_CHECK_EQUAL(r,4.0);
    
}


BOOST_AUTO_TEST_SUITE_END()

//=============================================================
//==================== SPECTRAL ROLLOFF =======================
//=============================================================
BOOST_AUTO_TEST_SUITE(SpectralRolloff)

// ------------------------------------------------------------
// 1. Check that a buffer of ones returns the threshold (given rounding errors due to indexing)
BOOST_AUTO_TEST_CASE(Ones_Test)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum (512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 1;
    }
    
    float r = fdf.spectralRolloff (testSpectrum, 0.85);
    
    BOOST_CHECK_EQUAL (r, roundf(0.85 * 512.) / 512.);
}


// ------------------------------------------------------------
// 2. Check that a buffer of zeros returns 0
BOOST_AUTO_TEST_CASE(Zeros_Test)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum (512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 0;
    }
    
    float r = fdf.spectralRolloff (testSpectrum, 0.85);
    
    BOOST_CHECK_EQUAL (r, 0.0);
    
}

// ------------------------------------------------------------
// 3. Numeric Example
BOOST_AUTO_TEST_CASE(NumericTest)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum (512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = i;
    }
    
    float r1 = fdf.spectralRolloff (testSpectrum);
    
    BOOST_CHECK_EQUAL (r1, 0.921875);
    
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = (512-i - 1);
    }
    
    float r2 = fdf.spectralRolloff (testSpectrum);
    
    BOOST_CHECK_EQUAL (r2, 0.611328125);
    
}

BOOST_AUTO_TEST_SUITE_END()


//=============================================================
//==================== SPECTRAL KURTOSIS ======================
//=============================================================
BOOST_AUTO_TEST_SUITE(SpectralKurtosis)

// ------------------------------------------------------------
// 1. Check that a buffer of ones returns -3.
BOOST_AUTO_TEST_CASE(Ones_Test)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum (512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 1;
    }
    
    float r = fdf.spectralKurtosis (testSpectrum);
    
    BOOST_CHECK_EQUAL (r, -3.);
}


// ------------------------------------------------------------
// 2. Check that a buffer of zeros returns -3.
BOOST_AUTO_TEST_CASE(Zeros_Test)
{
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testSpectrum (512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = 0;
    }
    
    float r = fdf.spectralKurtosis (testSpectrum);
    
    BOOST_CHECK_EQUAL (r, -3.);
    
}
 
// ------------------------------------------------------------
// 3. Numeric Example 1
BOOST_AUTO_TEST_CASE(NumericTest1)
{
    CoreFrequencyDomainFeatures<double> fdf;
    
    std::vector<double> testSpectrum (512);
    
    for (int i = 0;i < 512;i++)
    {
        testSpectrum[i] = i;
    }
    
    double r = fdf.spectralKurtosis (testSpectrum);
        
    BOOST_CHECK_CLOSE (r, -1.20000915531, 0.000001);
}

// ------------------------------------------------------------
// 4. Numeric Example 2
BOOST_AUTO_TEST_CASE(NumericTest2)
{
    CoreFrequencyDomainFeatures<double> fdf;
    
    std::vector<double> testSpectrum (512);
    
    for (int i = 0;i < 512;i++)
    {
        if (i % 2 == 0)
        {
            testSpectrum[i] = 1;
        }
        else
        {
            testSpectrum[i] = 0;
        }
    }
    
    double r = fdf.spectralKurtosis (testSpectrum);
    
    BOOST_CHECK_CLOSE (r, -2.0, 0.000001);
}

// ------------------------------------------------------------
// 5. Numeric Example 3
BOOST_AUTO_TEST_CASE(NumericTest3)
{
    CoreFrequencyDomainFeatures<double> fdf;
    
    std::vector<double> testSpectrum (512);
    
    for (int i = 0;i < 512;i++)
    {
        if (i % 10 == 0)
        {
            testSpectrum[i] = 1;
        }
        else
        {
            testSpectrum[i] = 0;
        }
    }
    
    double r = fdf.spectralKurtosis (testSpectrum);
    
    BOOST_CHECK_CLOSE (r, 4.95919732441, 0.000001);
}

BOOST_AUTO_TEST_SUITE_END()

#endif
