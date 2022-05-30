/**
 * @file main.cpp
 * @brief Main entry point. 
 */

// #include "cmdline.hpp"
// #include "gallery.hpp"
// #include "image.hpp"
// #include "bmpimage.hpp"
// #include "output.hpp"
// #include "asciiart.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

#define D if(0)

using namespace std;

struct rgba
{
    uint8_t b, g, r, a;
};

class CImage
{
public:
    CImage ( string filepath ) 
    {
        loadInput( filepath );
        init();
        fillPixels();
        fillPallete();
        convertGray();
        stretch();
    }
    ~CImage() {}
    void loadInput( string & filepath )
    {
        fstream f ( filepath, ios::in | ios::binary );
        if ( !f.is_open () ) 
            throw std::invalid_argument ( "Error: File Not Found." );
        
        D cout << "check 1" << endl;
        int fileHeaderSize = 14;
        vector<uint8_t> fileHeader ( fileHeaderSize );
        f.read ( reinterpret_cast<char*> ( fileHeader.data() ), fileHeaderSize);
        m_fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4]  << 16) + (fileHeader[5]  << 24);
        m_index    = fileHeader[10] + (fileHeader[11] << 8) + (fileHeader[12]  << 16) + (fileHeader[13]  << 24);

        f.seekg ( 0, ios::beg );
        m_buffer.resize(m_fileSize);
        f.read ( reinterpret_cast<char*> ( m_buffer.data() ), m_fileSize);
        f.close();
        D cout << "m_buffer.size() = " << m_buffer.size() << endl;
    }
    void init()
    {
        m_width  = m_buffer[18] + (m_buffer[19] << 8) + (m_buffer[20] << 16) + (m_buffer[21] << 24);
        m_height = m_buffer[22] + (m_buffer[23] << 8) + (m_buffer[24] << 16) + (m_buffer[25] << 24);
        D cout << dec << "size = "   << m_fileSize << endl;
        D cout << dec << "width = "  << m_width    << endl;
        D cout << dec << "height = " << m_height   << endl;
        m_paddingAmount = ((4 - (m_width*3) % 4 ) % 4 );
    }
    void fillPixels()
    {
        m_pixels.resize( m_width * m_height );
        for (int h = m_height - 1; h >= 0; h--)
        {
            for (int w = 0; w < m_width; w++)
            {                
                // m_pixels[h * m_width + w].b = (float) m_buffer[m_index] / 255.0f;
                m_pixels[h * m_width + w].b = (float) m_buffer[m_index];
                m_index++;
                m_pixels[h * m_width + w].g = (float) m_buffer[m_index];
                m_index++;
                m_pixels[h * m_width + w].r = (float) m_buffer[m_index];
                m_index++;
                m_pixels[h * m_width + w].a = (float) m_buffer[m_index];
                m_index++;
                // m_pixels[h * m_width + w].a = 255;
            }
        }
        m_index += m_paddingAmount;
        D cout << "check 2" << endl;
    }
    void fillPallete()
    {
        // m_pallete = " .v5P@";
        m_pallete = "@8P0DOCwocui;:,. ";
        // m_pallete = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    }
    void convertGray()
    {
        int len = m_pixels.size();
        for (int i = 0; i < len; i++)
        {
            // int sum = (float) m_pixels[i].b * 0  + (float) m_pixels[i].g * 0.9+ (float) m_pixels[i].r * 0.1 ;
            int sum = (float) m_pixels[i].b * 0.114  + (float) m_pixels[i].g * 0.587+ (float) m_pixels[i].r * 0.299 ;
            m_grayVec.push_back( sum );
        } 
    }
    char convertAscii( int index )
    {
        int charSize = 256;
        int palSize = m_pallete.size();
        double res = ( (double) m_grayVec[index] / charSize ) * palSize;
        return m_pallete[res];
    }
    void printArt()
    {
        int index = 0;
        // int index = i*m_width + k;
        cout << "ASCII - ART" << endl;
        for (int i = 0; i < m_height; i++)
        {
            for (int k = 0; k < m_width; k++)
            {
                cout << convertAscii( index );
                index ++;
            }
            cout << endl;
        }   
    }
    void stretch()
    {
        // vector<uint8_t> tmp;
        // int s = m_grayVec.size();
        // for (int i = 0; i < s; i++)
        // {
        //     tmp.push_back( m_grayVec[i] );
        //     tmp.push_back( m_grayVec[i] );
        // }
        // m_width *= 2;
        // m_grayVec = tmp;        
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
    void minimalise()
    {
        vector<uint8_t> tmp;
        for (int h = 0; h < m_height-1; h+=2)
        {
            for (int w = 0; w < m_width-1; w+=2)
            {
                int sum = (m_grayVec[h*m_width + w] + m_grayVec[h*m_width + w + 1] + m_grayVec[(h+1)*m_width + w] + m_grayVec[(h+1)*m_width + w + 1]) / 4;
                tmp.push_back( sum );
            }
        }
        m_grayVec = tmp;
        m_height /= 2;
        m_width /= 2;
    }
    void maximalise()
    {

    }
    void dumpPixels()
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
    void dumpPallete()
    {
        cout << "pallete >";
        for (int i = 0; i < m_pallete.size(); i++)
        {
            cout << m_pallete[i];
        }
        cout << "<" << endl;  
    }
    void dumpGrayVec()
    {
        cout << "grayVec:" << endl;
        for (int i = 0; i < m_grayVec.size(); i++)
        {
            cout << hex << (int) m_grayVec[i] << " | ";
        }
        cout << endl; 
    }
    void printHeadline()
    {
        cout << "_____/\\\\\\\\\\\\\\\\\\________/\\\\\\\\\\\\\\\\\\\\\\__________/\\\\\\\\\\\\\\\\\\__/\\\\\\\\\\\\\\\\\\\\\\__/\\\\\\\\\\\\\\\\\\\\\\_\n";
        cout << " ___/\\\\\\\\\\\\\\\\\\\\\\\\\\____/\\\\\\/////////\\\\\\_____/\\\\\\////////__\\/////\\\\\\///__\\/////\\\\\\///__                    \n";
        cout << "  __/\\\\\\/////////\\\\\\__\\//\\\\\\______\\///____/\\\\\\/_______________\\/\\\\\\_________\\/\\\\\\_____                           \n";
        cout << "   _\\/\\\\\\_______\\/\\\\\\___\\////\\\\\\__________/\\\\\\_________________\\/\\\\\\_________\\/\\\\\\_____                         \n";
        cout << "    _\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\______\\////\\\\\\______\\/\\\\\\_________________\\/\\\\\\_________\\/\\\\\\_____               \n";
        cout << "     _\\/\\\\\\/////////\\\\\\_________\\////\\\\\\___\\//\\\\\\________________\\/\\\\\\_________\\/\\\\\\_____                       \n";
        cout << "      _\\/\\\\\\_______\\/\\\\\\__/\\\\\\______\\//\\\\\\___\\////\\\\\\\\\\\\\\\\\\\\\\_____\\/\\\\\\_________\\/\\\\\\_____          \n";
        cout << "       _\\///________\\///____\\///////////___________\\/////////__\\///////////__\\///////////__                                      \n";   
    }

private:
    int             m_fileSize;
    int             m_width;
    int             m_height;
    vector<uint8_t> m_buffer; // storing raw input
    int             m_index; // where to read from m_buffer
    vector<rgba>    m_pixels; // storing rgba pixels
    int             m_paddingAmount;
    string          m_pallete; // storing available char for output
    vector<uint8_t> m_grayVec; // storing 8bit average for each pixel
};

int main ( int argc, char** argv )
{   
    D cout << "start" << endl;
    // string path = "img/beruska-lo.bmp";
    string path = "img/cat.bmp";
    CImage img( path );
    img.printArt();

    D cout << "OK" << endl;

    return 0;
}
