#include <iostream>
#include <vector>
#include <iomanip>

#include "rgba.hpp"
#include "CPixelMap.hpp"

using namespace std;

CPixelMap::CPixelMap ( const int height, const int width )
{
    m_height = height;
    m_width  = width;
    m_pixels.resize( m_height * m_width );
}
void CPixelMap::setPixels( const int i, const rgba pix ) 
{
    m_pixels[ i ] = pix;
}
void CPixelMap::dumpPixels() const
{
    for (size_t i = 0; i < m_pixels.size(); i++)
    {
        cout << hex << 
        setfill('0') << setw(2) << (int) m_pixels[i].r << " " << 
        setfill('0') << setw(2) << (int) m_pixels[i].g << " " << 
        setfill('0') << setw(2) << (int) m_pixels[i].g << " " << 
        setfill('0') << setw(2) << (int) m_pixels[i].a << endl;
    }
}
void CPixelMap::convertToGray()
{
    m_grayPixels.clear();
    size_t len = m_pixels.size();
    for (size_t i = 0; i < len; i++)
    {
        int sum = (float) m_pixels[i].b * 0.114 + (float) m_pixels[i].g * 0.587+ (float) m_pixels[i].r * 0.299 ;
        m_grayPixels.push_back( sum );
    } 
}
size_t CPixelMap::getWidth() const
{
    return m_width;
}
size_t CPixelMap::getHeight() const
{
    return m_height;
}
vector<uint8_t> CPixelMap::getGrayPixels() const
{
    return m_grayPixels;
}
vector<uint8_t> & CPixelMap::getGrayPixelsRef()
{
    return m_grayPixels;
}
void CPixelMap::setHeight( const int newHeight )
{
    m_height = newHeight;
}
void CPixelMap::setGrayPixels( const vector<uint8_t> newGrayPixels )
{
    m_grayPixels = newGrayPixels;
}