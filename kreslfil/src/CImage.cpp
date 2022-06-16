#include <iostream>
#include <iomanip>
#include <vector>

#include "CImage.hpp"

using namespace std;

CImage::CImage( CPixelMap pixMap  )
{
    m_width      = pixMap.getWidth();
    m_height     = pixMap.getHeight();
    m_grayPixels = pixMap.getGrayPixels();
}
void CImage::dumpPixels() const
{
    for (size_t i = 0; i < m_grayPixels.size(); i++)
    {
        cout << dec << setfill('0') << setw(2) << (int) m_grayPixels[i] << endl;
    }
    cout << "--------" << endl;
}
vector<uint8_t> CImage::getGrayPixels() const
{
    return m_grayPixels;
}
size_t CImage::getWidth() const
{
    return m_width;
}
size_t CImage::getHeight() const
{
    return m_height;
}
