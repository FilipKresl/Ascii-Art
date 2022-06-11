#include "CPixelMap.hpp"

using namespace std;

#pragma once

class CImage
{
public:
    CImage( CPixelMap pixMap );
    void dumpPixels();
    size_t getWidth();
    size_t getHeight();
    vector<uint8_t> getGrayPixels();

protected:
    size_t m_width;
    size_t m_height;
    vector<uint8_t> m_grayPixels;
};