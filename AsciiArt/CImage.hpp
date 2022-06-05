#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#pragma once

using namespace std;

#define D if(0)

struct rgba
{
    uint8_t b, g, r, a;
};

class CImage
{
public:
    virtual ~CImage() {}
    virtual void loadImg ( const string & filepath, bool bdoStretch ) = 0;
    virtual void init ( bool bdoStretch ) = 0;
    virtual void fillPixels () = 0;
    void convertGray ()
    {
        int len = m_pixels.size();
        for (int i = 0; i < len; i++)
        {
            int sum = (float) m_pixels[i].b * 0.114  + (float) m_pixels[i].g * 0.587+ (float) m_pixels[i].r * 0.299 ;
            m_grayVec.push_back( sum );
        } 
    }
    void stretch ()
    {       
        vector<uint8_t> tmp;
        for (int h = 0; h < m_height-1; h+=2)
        {
            for (int w = 0; w < m_width; w++)
            {
                tmp.push_back( (m_grayVec[h*m_width + w] + m_grayVec[(h+1)*m_width + w]) / 2 );
            }
        }
        
        m_height /= 2;
        m_grayVec = tmp;        
    }
    void dumpPixels ()
    {
        for (int i = 0; i < m_pixels.size(); i++)
        {
            cout << hex << setfill('0') << setw(2) << (int) m_pixels[i].b << " ";
            cout << hex << setfill('0') << setw(2) << (int) m_pixels[i].g << " ";
            cout << hex << setfill('0') << setw(2) << (int) m_pixels[i].r << " ";
            cout << hex << setfill('0') << setw(2) << (int) m_pixels[i].a;
            cout << endl;
        }
    }
    void dumpGrayVec ()
    {
        cout << "grayVec:" << endl;
        for (int i = 0; i < m_grayVec.size(); i++)
        {
            cout << hex << (int) m_grayVec[i] << " | ";
        }
        cout << endl; 
    }
    int getHeight ()
    {
        return m_height;
    }
    int getWidth ()
    {
        return m_width;
    }
    vector<uint8_t> getGrayVec ()
    {
        return m_grayVec;
    }
protected:
    int             m_fileSize;
    int             m_width;
    int             m_height;
    vector<uint8_t> m_buffer; // storing raw input
    int             m_index; // where to read from m_buffer
    vector<rgba>    m_pixels; // storing rgba pixels
    int             m_paddingAmount;
    vector<uint8_t> m_grayVec; // storing 8bit average for each pixel
};

class CImageBMP : public CImage
{
public:
    virtual void loadImg( const string & filepath, bool bdoStretch )
    {
        fstream f ( filepath, ios::in | ios::binary );
        if ( !f.is_open () ) 
            throw invalid_argument ( "Error: File Not Found." );
        
        int fileHeaderSize = 14;
        vector<uint8_t> fileHeader ( fileHeaderSize );
        f.read ( reinterpret_cast<char*> ( fileHeader.data() ), fileHeaderSize);
        m_fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4]  << 16) + (fileHeader[5]  << 24);
        m_index    = fileHeader[10] + (fileHeader[11] << 8) + (fileHeader[12]  << 16) + (fileHeader[13]  << 24);

        f.seekg ( 0, ios::beg );
        m_buffer.resize(m_fileSize);
        f.read ( reinterpret_cast<char*> ( m_buffer.data() ), m_fileSize);
        f.close();

        init( bdoStretch );
        D dumpPixels();
        D dumpGrayVec();
    }
    virtual void init ( bool bdoStretch )
    {
        m_width  = m_buffer[18] + (m_buffer[19] << 8) + (m_buffer[20] << 16) + (m_buffer[21] << 24);
        m_height = m_buffer[22] + (m_buffer[23] << 8) + (m_buffer[24] << 16) + (m_buffer[25] << 24);
        m_paddingAmount = ((4 - (m_width*3) % 4 ) % 4 );
        fillPixels();
        convertGray();
        if ( bdoStretch )
            stretch();
    }
    virtual void fillPixels ()
    {
        m_pixels.resize( m_width * m_height );
        for (int h = m_height - 1; h >= 0; h--)
        {
            for (int w = 0; w < m_width; w++)
            {                
                m_pixels[h * m_width + w].b = (float) m_buffer[m_index];
                m_index++;
                m_pixels[h * m_width + w].g = (float) m_buffer[m_index];
                m_index++;
                m_pixels[h * m_width + w].r = (float) m_buffer[m_index];
                m_index++;
                m_pixels[h * m_width + w].a = (float) m_buffer[m_index];
                m_index++;
            }
        }
        m_index += m_paddingAmount;
    }
};

class CImageTGA : public CImage
{
    virtual void loadImg( const string & filepath, bool bdoStretch )
    {
        fstream f ( filepath, ios::in | ios::binary );
        if ( !f.is_open () ) 
            throw invalid_argument ( "Error: File Not Found." );
        
        f.seekg ( 0, ios::beg );
        streampos beg = f.tellg();
        f.seekg ( 0, ios::end );
        streampos end = f.tellg();
        m_fileSize = end - beg;
        f.seekg ( 0, ios::beg );
        m_buffer.resize(m_fileSize);
        f.read ( reinterpret_cast<char*> ( m_buffer.data() ), m_fileSize);
        f.close();

        // vector<uint8_t> fileHeader ( fileHeaderSize );
        // f.read ( reinterpret_cast<char*> ( fileHeader.data() ), fileHeaderSize);
        m_width    = m_buffer[12] + ( m_buffer[13] << 8 );
        m_height   = m_buffer[14] + ( m_buffer[15] << 8 );
        m_index    = 18;

        // f.seekg ( 0, ios::beg );
        // m_buffer.resize(m_fileSize);
        // f.read ( reinterpret_cast<char*> ( m_buffer.data() ), m_fileSize);
        // f.close();

        init( bdoStretch );
        D dumpPixels();
        D dumpGrayVec();
    }
    virtual void init ( bool bdoStretch )
    {
        m_paddingAmount = 0;
        fillPixels();
        convertGray();
        if ( bdoStretch )
            stretch();
    }
    virtual void fillPixels ()
    {
        cout << "size = " << m_fileSize << endl;
        cout << "m_width = " << m_width << " m_height = " << m_height << endl;
        m_pixels.resize( m_width * m_height );
        for (int h = 0; h < m_height; h++)
        {
            for (int w = 0; w < m_width; w++)
            {                
                m_pixels[h * m_width + w].b = (float) m_buffer[m_index];
                m_index++;
                m_pixels[h * m_width + w].g = (float) m_buffer[m_index];
                m_index++;
                m_pixels[h * m_width + w].r = (float) m_buffer[m_index];
                m_index++;
                m_pixels[h * m_width + w].a = 0;
            }
        }
        m_index += m_paddingAmount;
    }
};

class CImageRAW : public CImage
{
};
