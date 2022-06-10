#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

#include "CFormatBMP.hpp"

vector<uint8_t> CFormatBMP::load ( const string & filename )
{
    cout << "check bmp 1" << endl;
    fstream f ( filename, ios::in | ios::binary );
    if ( !f.is_open () ) 
        throw invalid_argument ( "File Not Found" );
    
    int fileHeaderSize = 14;
    vector<uint8_t> fileHeader ( fileHeaderSize );
    f.read ( reinterpret_cast<char*> ( fileHeader.data() ), fileHeaderSize);
    // validate
    int fileSize = fileHeader[2]  + (fileHeader[3]  << 8) + (fileHeader[4]  << 16) + (fileHeader[5]  << 24);
    int index    = fileHeader[10] + (fileHeader[11] << 8) + (fileHeader[12] << 16) + (fileHeader[13] << 24);

    f.seekg ( 0, ios::beg );

    m_buffer.resize( fileSize );
    f.read ( reinterpret_cast<char*> ( m_buffer.data() ), fileSize);
    // validate
    f.close();

    int width  = m_buffer[18] + (m_buffer[19] << 8) + (m_buffer[20] << 16) + (m_buffer[21] << 24);
    int height = m_buffer[22] + (m_buffer[23] << 8) + (m_buffer[24] << 16) + (m_buffer[25] << 24);
    CPixelMap pixMap( height, width );

    fillPixelMap( width, height, index, pixMap );

    // init( bdoStretch );
    return pixMap.getGreyPixels();
}
void CFormatBMP::fillPixelMap ( int width, int height, int index, CPixelMap & rpixMap ) 
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
