#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GistTests
#include <boost/test/unit_test.hpp>

/*
#include <iostream>
#include <time.h>
#include "../../src/Gist.h"
#include "test-signals/Test_Signals.h"

int main()
{
    Gist<float> g(512,44100);
    
    std::vector<float> frame;
    
    for (int i = 0;i < 512;i++)
    {
        frame.push_back(pitchTest1[i]);
    }
    
    float r;
    
    g.processAudioFrame(frame);
    
    clock_t t;
    t = clock();
    
    
    for (int i = 0; i < 1000; i++)
    {
        r = g.pitchYin();
        //r = g.rootMeanSquare();
    }
    
    
    t = clock() - t;
    printf ("It took Kiss FFT %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    
    
    std::cout << "pitch was " << r << std::endl;
    
    return 0;
}
*/