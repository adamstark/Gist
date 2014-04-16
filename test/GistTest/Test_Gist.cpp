#ifndef GIST_TESTS
#define GIST_TESTS

#include "../../src/Gist.h"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

//=============================================================
//========================= GIST ==============================
//=============================================================
BOOST_AUTO_TEST_SUITE(GistTest)

//=============================================================
BOOST_AUTO_TEST_CASE(TestFFT1)
{
    Gist<float> g(512,44100);
    
    std::vector<float> testFrame(512);
    
    for (int i = 0;i < 512;i++)
    {
        testFrame[i] = 0;
    }
    
    testFrame[0] = 1.0;
    
    g.processAudioFrame(testFrame);
    
    std::vector<float> mag;
    
    mag = g.getMagnitudeSpectrum();
    
    for (int i = 0;i < mag.size();i++)
    {
        BOOST_CHECK_EQUAL(mag[i], 1.0);
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE(TestFFT2)
{
    Gist<float> g(512,44100);
        
    std::vector<float> testFrame(512);
    
    for (int i = 0;i < 512;i++)
    {
        testFrame[i] = 1.0;
    }
    
    g.processAudioFrame(testFrame);
    
    std::vector<float> mag;
    
    mag = g.getMagnitudeSpectrum();
    
    BOOST_CHECK_EQUAL(mag[0], testFrame.size());
    
    for (int i = 1;i < mag.size();i++)
    {
        BOOST_CHECK_EQUAL(mag[i], 0.0);
    }
}

//=============================================================
BOOST_AUTO_TEST_CASE(RMS_Test)
{
    Gist<float> g(512,44100);
    
    CoreTimeDomainFeatures<float> tdf;
    
    std::vector<float> testFrame(512);
    
    for (int i = 0;i < 512;i++)
    {
        testFrame[i] = ((float)((rand() % 1000) - 500)) / 1000.;
    }
    
    g.processAudioFrame(testFrame);
    
    float r1 = g.rootMeanSquare();
    
    float r2 = tdf.rootMeanSquare(testFrame);

    BOOST_CHECK_EQUAL(r1,r2);
    
}

//=============================================================
BOOST_AUTO_TEST_CASE(PeakEnergy_Test)
{
    Gist<float> g(512,44100);
    
    CoreTimeDomainFeatures<float> tdf;
    
    std::vector<float> testFrame(512);
    
    for (int i = 0;i < 512;i++)
    {
        testFrame[i] = ((float)((rand() % 1000) - 500)) / 1000.;
    }
    
    g.processAudioFrame(testFrame);
    
    float r1 = g.peakEnergy();
    
    float r2 = tdf.peakEnergy(testFrame);
    
    BOOST_CHECK_EQUAL(r1,r2);
    
}

//=============================================================
BOOST_AUTO_TEST_CASE(ZeroCrossingRate_Test)
{
    Gist<float> g(512,44100);
    
    CoreTimeDomainFeatures<float> tdf;
    
    std::vector<float> testFrame(512);
    
    for (int i = 0;i < 512;i++)
    {
        testFrame[i] = ((float)((rand() % 1000) - 500)) / 1000.;
    }
    
    g.processAudioFrame(testFrame);
    
    float r1 = g.zeroCrossingRate();
    
    float r2 = tdf.zeroCrossingRate(testFrame);
    
    BOOST_CHECK_EQUAL(r1,r2);
    
}

//=============================================================
BOOST_AUTO_TEST_CASE(SpectralCentroid_Test)
{
    Gist<float> g(512,44100);
    
    CoreFrequencyDomainFeatures<float> fdf;
    
    std::vector<float> testFrame(512);
    
    for (int i = 0;i < 512;i++)
    {
        testFrame[i] = ((float)((rand() % 1000) - 500)) / 1000.;
    }
    
    g.processAudioFrame(testFrame);
    
    float r1 = g.spectralCentroid();
    
    float r2 = fdf.spectralCentroid(g.getMagnitudeSpectrum());
    
    BOOST_CHECK_EQUAL(r1,r2);
    
}


BOOST_AUTO_TEST_SUITE_END()

#endif
