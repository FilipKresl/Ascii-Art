#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <chrono>

#include "CFormatBMP.hpp"
#include "CFlags.hpp"

CPixelMap CFormatBMP::load ( const string & filename, CFlags & rflags )
{ 
    fstream f ( filename, ios::in | ios::binary );
    if ( !f.is_open () ) 
        throw invalid_argument ( "File Not Found" );
    
    int fileHeaderSize = 14;
    vector<uint8_t> fileHeader ( fileHeaderSize );
    f.read ( reinterpret_cast<char*> ( fileHeader.data() ), fileHeaderSize);
    if ( !f )
        throw invalid_argument ( "Error while reading" );

    int fileSize = fileHeader[2]  + (fileHeader[3]  << 8) + (fileHeader[4]  << 16) + (fileHeader[5]  << 24);
    int index    = fileHeader[10] + (fileHeader[11] << 8) + (fileHeader[12] << 16) + (fileHeader[13] << 24);

    f.seekg( 0, ios::beg );
    m_buffer.resize( fileSize );
    f.read( reinterpret_cast<char*> ( m_buffer.data() ), fileSize);
    if ( !f )
        throw invalid_argument ( "Error while reading" );
    f.close();

    int width  = m_buffer[18] + (m_buffer[19] << 8) + (m_buffer[20] << 16) + (m_buffer[21] << 24);
    int height = m_buffer[22] + (m_buffer[23] << 8) + (m_buffer[24] << 16) + (m_buffer[25] << 24);
    CPixelMap pixMap( height, width );
    fillPixelMap( width, height, index, pixMap );

    if ( rflags.m_stretch )
        stretch( pixMap );
    return pixMap;
}
void CFormatBMP::fillPixelMap( int width, int height, int index, CPixelMap & rpixMap ) 
{
    int paddingAmount = ( ( 4 - (width*3) % 4 ) % 4 );
    for (int h = height - 1; h >= 0; h--)
    {
        for (int w = 0; w < width; w++)
        {
            rgba pix; 
            pix.b = (float) m_buffer[index];
            index++;
            pix.g = (float) m_buffer[index];
            index++;
            pix.r = (float) m_buffer[index];
            index++;
            pix.a = (float) m_buffer[index];
            index++;
            rpixMap.setPixels( h * width + w, pix );
        }
    }
    index += paddingAmount;
    rpixMap.convertToGray();
}
