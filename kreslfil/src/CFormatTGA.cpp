#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

#include "CFormatTGA.hpp"
#include "CFlags.hpp"

using namespace std;
vector<uint8_t> CFormatTGA::load ( const string & filename, CFlags & rflags )
{
    fstream f ( filename, ios::in | ios::binary );
    if ( !f.is_open () ) 
        throw invalid_argument ( "File Not Found" );

    int fileHeaderSize = 18;
    f.seekg ( 0, ios::beg );
    streampos beg = f.tellg();
    f.seekg ( 0, ios::end );
    streampos end = f.tellg();
    int fileSize = end - beg - fileHeaderSize;
    f.seekg ( 0, ios::beg );

    vector<uint8_t> fileHeader ( fileHeaderSize );
    f.read ( reinterpret_cast<char*> ( fileHeader.data() ), fileHeaderSize);
    if ( !f )
        throw invalid_argument ( "Error while reading" );

    int width  = fileHeader[12] + ( fileHeader[13] << 8 );
    int height = fileHeader[14] + ( fileHeader[15] << 8 );
    int index  = 0;

    vector<uint8_t> buffer;
    m_buffer.resize( fileSize );
    f.read ( reinterpret_cast<char*> ( m_buffer.data() ), fileSize);
    if ( !f )
        throw invalid_argument ( "Error while reading" );

    f.close();

    CPixelMap pixMap( height, width );

    fillPixelMap( width, height, index, pixMap );
    return pixMap.getGreyPixels();
}
void CFormatTGA::fillPixelMap ( int width, int height, int index, CPixelMap & rpixMap )
{
    for (int h = 0; h < height; h++)
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
            pix.a = 255;
            rpixMap.setPixels( h * width + w, pix );
        }
    }
    rpixMap.convertToGray();
}
