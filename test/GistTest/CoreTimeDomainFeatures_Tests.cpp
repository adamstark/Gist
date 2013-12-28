#ifndef CORE_TIME_DOMAIN_FEATURES_TESTS
#define CORE_TIME_DOMAIN_FEATURES_TESTS

#include "../../src/gist.h"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

//=============================================================
BOOST_AUTO_TEST_SUITE(RMS)

// 1. Check that a buffer of zeros returns zero
BOOST_AUTO_TEST_CASE(Zero_Test)
{
    CoreTimeDomainFeatures td;
    
    std::vector<float> testFrame(512);
    
    for (int i = 0;i < 512;i++)
    {
        testFrame[i] = 0;
    }
    
    float r = td.RMS(testFrame);

    BOOST_CHECK_EQUAL(r,0.0);
    
}

BOOST_AUTO_TEST_SUITE_END()


#endif
