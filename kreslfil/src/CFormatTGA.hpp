#include <iostream>
#include <string>

#include "CPixelMap.hpp"
#include "CFormat.hpp"
#include "CFlags.hpp"

#pragma once

using namespace std;

class CFormatTGA : public CFormat
{
    CPixelMap load ( const string & filename, CFlags & rflags ) override;
    void fillPixelMap ( int width, int height, int index, CPixelMap & rpixMap ) override;
};