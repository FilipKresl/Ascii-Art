#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <assert.h>

#include "CGallery.hpp"
#include "CFlags.hpp"
#include "CEffectManager.hpp"
#include "COutputDebug.hpp"
#include "CTests.hpp"

using namespace std;

CTests::CTests()
{
    testLoading();
    testLights();

}
void CTests::testLoading()
{
    CFlags flags;
    flags.m_stretch = false;

    vector<string> pathsA = {"assets/img/3x3.bmp"};
    CGallery galA( pathsA, flags );
    CImage * pimgA = galA.getImage();
    vector<string> pathsB = {"assets/img/3x3.tga"};
    CGallery galB( pathsB, flags );
    CImage * pimgB = galB.getImage();

    vector<uint8_t> testGray = {253,1,1,1,1,149,76,2,3};
    assert ( pimgA->getGrayPixels() == testGray );
    assert ( pimgB->getGrayPixels() == testGray );
}
void CTests::testLights()
{
    CFlags flags;
    vector<string> paths = {"assets/img/johnny.bmp"};
    CGallery gal( paths, flags );
    CImage * pimg = gal.getImage();

    COutputDebug outD;
    outD.readImg( pimg );
    vector<uint8_t> testLightA = outD.getGrays();
    outD.lightUp();
    vector<uint8_t> testLightB = outD.getGrays();

    assert ( testLightA.size() == testLightB.size() );
    for (size_t i = 0; i < testLightA.size(); i++)
    {
        if ( testLightB[i] != 255 || testLightA[i] != 255 )
            assert ( testLightB[i] > testLightA[i] );
    }
}
