#include "CPixelMap.hpp"
#include "CFormat.hpp"
#include "CFlags.hpp"

#pragma once

using namespace std;

class CFormatBMP : public CFormat
{
public:
    CPixelMap load ( const string & filename, CFlags & rflags ) override;
    
    void fillPixelMap ( int width, int height, int index, CPixelMap & rpixMap ) override;
};
