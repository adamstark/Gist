#ifndef PITCH_TESTS
#define PITCH_TESTS

#include "../../src/Gist.h"
#include "test-signals/Test_Signals.h"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

//=============================================================
//========================= YIN ===============================
//=============================================================
BOOST_AUTO_TEST_SUITE(PitchYin)

// ------------------------------------------------------------
// 1. CHECK KNOWN BUFFER WITH KNOWN PITCH 1
BOOST_AUTO_TEST_CASE(Buffer_Test_1)
{
    Yin<float> y(44100);
    
    std::vector<float> frame;
    
    for (int i = 0;i < 512;i++)
    {
        frame.push_back(pitchTest1[i]);
    }
    
    float r = y.pitchYin(frame);
    

    BOOST_CHECK_CLOSE(r,pitchTest1_result,0.0001);
}

// ------------------------------------------------------------
// 2. CHECK KNOWN BUFFER WITH KNOWN PITCH 2
BOOST_AUTO_TEST_CASE(Buffer_Test_2)
{
    Yin<float> y(44100);
    
    std::vector<float> frame;
    
    for (int i = 0;i < 512;i++)
    {
        frame.push_back(pitchTest2[i]);
    }
    
    float r = y.pitchYin(frame);
    
    
    BOOST_CHECK_CLOSE(r,pitchTest2_result,0.0001);
}

// ------------------------------------------------------------
// 3. CHECK BUFFER OF ZEROS
BOOST_AUTO_TEST_CASE(ZeroTest)
{
    Yin<float> y(44100);
    
    std::vector<float> frame;
    
    for (int i = 0;i < 512;i++)
    {
        frame.push_back(0.0);
    }
    
    float r = y.pitchYin(frame);
        
    BOOST_CHECK_EQUAL(r,y.getMaxFrequency());
}

// ------------------------------------------------------------
// 4. CHECK BUFFER OF ONES (i.e. positive flat signal)
BOOST_AUTO_TEST_CASE(OnesTest)
{
    Yin<float> y(44100);
    
    std::vector<float> frame;
    
    for (int i = 0;i < 512;i++)
    {
        frame.push_back(1.0);
    }
    
    float r = y.pitchYin(frame);
    
    BOOST_CHECK_EQUAL(r,y.getMaxFrequency());
}

// ------------------------------------------------------------
// 5. CHECK BUFFER OF NEGATIVE ONES (i.e. negative flat signal)
BOOST_AUTO_TEST_CASE(NegativeOnesTest)
{
    Yin<float> y(44100);
    
    std::vector<float> frame;
    
    for (int i = 0;i < 512;i++)
    {
        frame.push_back(-1.0);
    }
    
    float r = y.pitchYin(frame);
    
    BOOST_CHECK_EQUAL(r,y.getMaxFrequency());
}

BOOST_AUTO_TEST_SUITE_END()

#endif
