#include <vector>

#include "rgba.hpp"
#include "CFlags.hpp"

#pragma once

using namespace std;

class CFormat
{
public:
    virtual ~CFormat() {}
    virtual vector<uint8_t> load ( const string & filename, CFlags & rflags ) = 0;
    virtual void fillPixelMap ( int width, int height, int index, CPixelMap & rpixMap ) = 0;
protected:
    vector<uint8_t> m_buffer;
};