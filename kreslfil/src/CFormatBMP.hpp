#include "CPixelMap.hpp"
#include "CFormat.hpp"
#include "CFlags.hpp"

#pragma once

using namespace std;

class CFormatBMP : public CFormat
{
public:
    vector<uint8_t> load ( const string & filename, CFlags & rflags ) override;
    
    void fillPixelMap ( int width, int height, int index, CPixelMap & rpixMap ) override;
};
