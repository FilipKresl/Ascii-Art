#include <iostream>
#include <vector>
#include <iomanip>

#include "rgba.hpp"

#pragma once

using namespace std;

class CPixelMap
{
public:
    CPixelMap ( int height, int width )
    {
        m_height = height;
        m_width  = width;
        m_pixels.resize( m_height * m_width );
    }
    void setPixels( int i, rgba pix ) 
    {
        m_pixels[ i ] = pix;
    }
    void dumpPixels() 
    {
        for (int i = 0; i < m_pixels.size(); i++)
        {
            cout << hex << 
            setfill('0') << setw(2) << (int) m_pixels[i].r << " " << 
            setfill('0') << setw(2) << (int) m_pixels[i].g << " " << 
            setfill('0') << setw(2) << (int) m_pixels[i].g << " " << 
            setfill('0') << setw(2) << (int) m_pixels[i].a << endl;
        }
    }
    void convertToGray()
    {
        m_greyPixels.clear();
        size_t len = m_pixels.size();
        for (size_t i = 0; i < len; i++)
        {
            int sum = (float) m_pixels[i].b * 0.114 + (float) m_pixels[i].g * 0.587+ (float) m_pixels[i].r * 0.299 ;
            m_greyPixels.push_back( sum );
        } 
    }
    vector<uint8_t> getGreyPixels()
    {
        return m_greyPixels;
    }
private:
    size_t m_width;
    size_t m_height;
    vector<rgba> m_pixels;
    vector<uint8_t> m_greyPixels;
};
