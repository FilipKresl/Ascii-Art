/**
 * @file CImage.hpp
 * @brief (base) CImage, (derived) CImageBMP, (derived) CImageTGA
 */
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

#pragma once

using namespace std;

/**
 * @brief struct for stoirng info about one pixel: Blue, Green, Red, Alpha
 */
struct rgba
{
    uint8_t b, g, r, a;
};

/**
 * @brief base Class for initializing the image and enabling basic editing
 */
class CImage
{
public:
    virtual ~CImage() {}
    /**
     * @brief pure virtual method for loading the image
     * 
     * @param filepath to the image
     * @param bdoStretch if should be stretched
     */
    virtual void loadImg ( const string & filepath, bool bdoStretch ) = 0;
    /**
     * @brief pure virtual method for initializing th eimage
     * @param bdoStretch if should be stretched
     */
    void dumpPixels ()
    {
        for (size_t i = 0; i < m_pixels.size(); i++)
        {
            cout << hex << setfill('0') << setw(2) << (int) m_pixels[i].b << " ";
            cout << hex << setfill('0') << setw(2) << (int) m_pixels[i].g << " ";
            cout << hex << setfill('0') << setw(2) << (int) m_pixels[i].r << " ";
            cout << hex << setfill('0') << setw(2) << (int) m_pixels[i].a;
            cout << endl;
        }
    }
    /**
     * @brief debug method for printing vector containing pixels converted to grayscale 8-bit number
     */
    void dumpGrayVec ()
    {
        cout << "grayVec:" << endl;
        for (size_t i = 0; i < m_grayVec.size(); i++)
        {
            cout << hex << (int) m_grayVec[i] << " | ";
        }
        cout << endl; 
    }
    /**
     * @brief getter for the height of an image
     * @return the height of an image 
     */
    int getHeight ()
    {
        return m_height;
    }
    /**
     * @brief getter for the width of an image
     * @return the width of an image 
     */
    int getWidth ()
    {
        return m_width;
    }
    /**
     * @brief getter for vector containing pixels converted to grayscale 8-bit number
     * @return the vector 
     */
    vector<uint8_t> getGrayVec ()
    {
        return m_grayVec;
    }
protected:
    virtual void init ( bool bdoStretch ) = 0;
    /**
     * @brief pure virtual method for reading the image and storing pixels as rgba to a member vector
     */
    virtual void fillPixels () = 0;
    /**
     * @brief debug method for printing each pixel as rgba
     */
    /**
     * @brief method for converting rgba to grayscale
     */
    void convertGray ()
    {
        size_t len = m_pixels.size();
        for (size_t i = 0; i < len; i++)
        {
            int sum = (float) m_pixels[i].b * 0.114 + (float) m_pixels[i].g * 0.587+ (float) m_pixels[i].r * 0.299 ;
            m_grayVec.push_back( sum );
        } 
    }
    /**
     * @brief optically helps the image by letting each other row out
     * because of disproportion of an Ascii char space 
     * (height of an Ascii char space is almost twice as long as width)
     * the image would be "too narrow" and look unnatural
     */
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
/**
 * @brief derived class specifically made for processing BMP image
 */
class CImageBMP : public CImage
{
public:
    /**
     * @brief loads the BMP image
     * 
     * @param filepath to the image
     * @param bdoStretch if should be stretched
     */
    virtual void loadImg( const string & filepath, bool bdoStretch )
    {
        fstream f ( filepath, ios::in | ios::binary );
        if ( !f.is_open () ) 
            throw invalid_argument ( "File Not Found" );
        
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
    }
    /**
     * @brief initializes the BMP image
     * 
     * @param bdoStretch if should be stretched
     */
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
    /**
     * @brief stores pixels as rgba to a member vector
     */
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
/**
 * @brief derived class specifically made for processing TGA image
 */
class CImageTGA : public CImage
{
    /**
     * @brief loads the TGA image
     * 
     * @param filepath to the image
     * @param bdoStretch if should be stretched
     */
    virtual void loadImg( const string & filepath, bool bdoStretch )
    {
        fstream f ( filepath, ios::in | ios::binary );
        if ( !f.is_open () ) 
            throw invalid_argument ( "File Not Found" );
        
        f.seekg ( 0, ios::beg );
        streampos beg = f.tellg();
        f.seekg ( 0, ios::end );
        streampos end = f.tellg();
        m_fileSize = end - beg;
        f.seekg ( 0, ios::beg );
        m_buffer.resize(m_fileSize);
        f.read ( reinterpret_cast<char*> ( m_buffer.data() ), m_fileSize);
        f.close();

        m_width    = m_buffer[12] + ( m_buffer[13] << 8 );
        m_height   = m_buffer[14] + ( m_buffer[15] << 8 );
        m_index    = 18;

        init( bdoStretch );
    }
    /**
     * @brief initializes the TGA image
     * 
     * @param bdoStretch if should be stretched
     */
    virtual void init ( bool bdoStretch )
    {
        m_paddingAmount = 0;
        fillPixels();
        convertGray();
        if ( bdoStretch )
            stretch();
    }
    /**
     * @brief stores pixels as rgba to a member vector
     */
    virtual void fillPixels ()
    {
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

// class CImageRAW : public CImage
// {
// };

// other derived classes ...
