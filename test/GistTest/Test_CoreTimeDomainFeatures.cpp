#ifndef CORE_TIME_DOMAIN_FEATURES_TESTS
#define CORE_TIME_DOMAIN_FEATURES_TESTS

#include "../../src/Gist.h"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

//=============================================================
//========================= RMS ===============================
//=============================================================
BOOST_AUTO_TEST_SUITE(RMS)

// ------------------------------------------------------------
// 1. Check that a buffer of zeros returns zero
BOOST_AUTO_TEST_CASE(Zero_Test)
{
    CoreTimeDomainFeatures<float> tdf;
    
    std::vector<float> testFrame(512);
    
    for (int i = 0;i < 512;i++)
    {
        testFrame[i] = 0;
    }
    
    float r = tdf.rootMeanSquare(testFrame);
    
    BOOST_CHECK_EQUAL(r,0);
    
}

// ------------------------------------------------------------
// 2. Check that a buffer of all ones returns 1
BOOST_AUTO_TEST_CASE(Ones_Test)
{
    CoreTimeDomainFeatures<float> tdf;
    
    std::vector<float> testFrame(512);
    
    for (int i = 0;i < 512;i++)
    {
        testFrame[i] = 1;
    }
    
    float r = tdf.rootMeanSquare(testFrame);
    
    BOOST_CHECK_EQUAL(r,1);
    
}

// ------------------------------------------------------------
// 3. Numeric Example
BOOST_AUTO_TEST_CASE(Numeric_Example)
{
    CoreTimeDomainFeatures<float> tdf;
    
    std::vector<float> testFrame(6);
    
    testFrame[0] = 0;
    testFrame[1] = 1;
    testFrame[2] = 2;
    testFrame[3] = 3;
    testFrame[4] = 4;
    testFrame[5] = 5;
    
    float r = tdf.rootMeanSquare(testFrame);
    
    BOOST_CHECK_CLOSE(r,3.0276503540974917,0.01);
    
}

BOOST_AUTO_TEST_SUITE_END()


//=============================================================
//===================== PEAK ENERGY ===========================
//=============================================================
BOOST_AUTO_TEST_SUITE(PeakEnergy)

// ------------------------------------------------------------
// 1. Check that a buffer of zeros returns zero
BOOST_AUTO_TEST_CASE(Zero_Test)
{
    CoreTimeDomainFeatures<float> tdf;
    
    std::vector<float> testFrame(512);
    
    for (int i = 0;i < 512;i++)
    {
        testFrame[i] = 0;
    }
    
    float r = tdf.peakEnergy(testFrame);
    
    BOOST_CHECK_EQUAL(r,0);
    
}

// ------------------------------------------------------------
// 2. Check that passing the index returns the highest index
BOOST_AUTO_TEST_CASE(Max_Val_Test_1)
{
    CoreTimeDomainFeatures<float> tdf;
    
    int frameSize = 512;
    
    std::vector<float> testFrame(frameSize);
    
    for (int i = 0;i < frameSize;i++)
    {
        testFrame[i] = (float) i;
    }
    
    float r = tdf.peakEnergy(testFrame);
    
    BOOST_CHECK_EQUAL(r,frameSize-1);
    
}

// ------------------------------------------------------------
// 3. Numeric Example 1
BOOST_AUTO_TEST_CASE(Numeric_1)
{
    CoreTimeDomainFeatures<float> tdf;
    
    int frameSize = 6;
    
    std::vector<float> testFrame(frameSize);
    
    testFrame[0] = 0;
    testFrame[1] = 10;
    testFrame[2] = 2;
    testFrame[3] = 37;
    testFrame[4] = 17;
    testFrame[5] = 19;
    
    float r = tdf.peakEnergy(testFrame);
    
    BOOST_CHECK_EQUAL(r,37);
}

BOOST_AUTO_TEST_SUITE_END()

//=============================================================
//===================== ZERO CROSSING RATE ====================
//=============================================================
BOOST_AUTO_TEST_SUITE(ZeroCrossingRate)

// ------------------------------------------------------------
// 1. Check that a buffer of zeros returns zero
BOOST_AUTO_TEST_CASE(Zero_Test)
{
    CoreTimeDomainFeatures<float> tdf;
    
    std::vector<float> testFrame(512);
    
    for (int i = 0;i < 512;i++)
    {
        testFrame[i] = 0;
    }
    
    float r = tdf.zeroCrossingRate(testFrame);
    
    BOOST_CHECK_EQUAL(r,0);
    
}

// ------------------------------------------------------------
// 2. Check that a buffer that is all larger than 0 returns 0
BOOST_AUTO_TEST_CASE(LargerThanZero)
{
    CoreTimeDomainFeatures<float> tdf;
    
    std::vector<float> testFrame(512);
    
    for (int i = 0;i < 512;i++)
    {
        testFrame[i] = ((float) i+1) / 512;
    }
    
    float r = tdf.zeroCrossingRate(testFrame);
    
    BOOST_CHECK_EQUAL(r,0);
    
}

// ------------------------------------------------------------
// 3. Check that a buffer that is all 0 or less returns 0
BOOST_AUTO_TEST_CASE(ZeroOrLess)
{
    CoreTimeDomainFeatures<float> tdf;
    
    std::vector<float> testFrame(512);
    
    for (int i = 0;i < 512;i++)
    {
        testFrame[i] = ((float) -i) / 512;
    }
    
    float r = tdf.zeroCrossingRate(testFrame);
    
    BOOST_CHECK_EQUAL(r,0);
    
}

// ------------------------------------------------------------
// 4. NumericExample - check that three zero crossings produces 3 as a return value
BOOST_AUTO_TEST_CASE(NumericExample)
{
    CoreTimeDomainFeatures<float> tdf;
    
    std::vector<float> testFrame(6);
    
    testFrame[0] = 0;
    testFrame[1] = 0.1;
    testFrame[2] = 0.4;
    testFrame[3] = -0.3;
    testFrame[4] = -0.1;
    testFrame[5] = 0.3;

    float r = tdf.zeroCrossingRate(testFrame);
    
    BOOST_CHECK_EQUAL(r,3);
    
}

BOOST_AUTO_TEST_SUITE_END()

#endif
