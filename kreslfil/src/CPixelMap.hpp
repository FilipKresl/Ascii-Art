#include <iostream>
#include <vector>
#include <iomanip>

#include "rgba.hpp"

#pragma once

using namespace std;

class CPixelMap
{
public:
    CPixelMap ( int height, int width );
    void setPixels( int i, rgba pix );
    void dumpPixels();
    void convertToGray();
    size_t getWidth();
    size_t getHeight();
    vector<uint8_t> getGrayPixels();
    vector<uint8_t> & getGrayPixelsRef();
    void setHeight( int newHeight );
    void setGrayPixels( vector<uint8_t> newGrayPixels );
private:
    size_t m_width;
    size_t m_height;
    vector<rgba> m_pixels;
    vector<uint8_t> m_grayPixels;
};
