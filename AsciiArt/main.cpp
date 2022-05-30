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
        m_pallete.clear();
        m_pallete.push_back( '.' );
        m_pallete.push_back( ',' );
        m_pallete.push_back( 'i' );
        m_pallete.push_back( 'w' );
        m_pallete.push_back( '2' );
        m_pallete.push_back( '8' );
        m_pallete.push_back( '@' );
    }
    void convertGray()
    {
        int len = m_pixels.size();
        for (int i = 0; i < len; i++)
        {
            int sum = ( m_pixels[i].b + m_pixels[i].g + m_pixels[i].r ) / 3;
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
    vector<uint8_t> m_buffer; // storing input
    int             m_index; // where to read from m_buffer
    vector<rgba>    m_pixels;
    int             m_paddingAmount;
    vector<char>    m_pallete;
    vector<uint8_t> m_grayVec;
};

int main ( int argc, char** argv )
{   
    D cout << "start" << endl;
    string path = "img/10x3.bmp";
    CImage img( path );
    // D img.dumpPixels();
    // D img.dumpPallete();
    // D img.dumpGrayVec();
    img.printArt();

    D cout << "OK" << endl;

    cout << "_____/\\\\\\\\\\\\\\\\\\________/\\\\\\\\\\\\\\\\\\\\\\__________/\\\\\\\\\\\\\\\\\\__/\\\\\\\\\\\\\\\\\\\\\\__/\\\\\\\\\\\\\\\\\\\\\\_\n";
    cout << " ___/\\\\\\\\\\\\\\\\\\\\\\\\\\____/\\\\\\/////////\\\\\\_____/\\\\\\////////__\\/////\\\\\\///__\\/////\\\\\\///__                    \n";
    cout << "  __/\\\\\\/////////\\\\\\__\\//\\\\\\______\\///____/\\\\\\/_______________\\/\\\\\\_________\\/\\\\\\_____                           \n";
    cout << "   _\\/\\\\\\_______\\/\\\\\\___\\////\\\\\\__________/\\\\\\_________________\\/\\\\\\_________\\/\\\\\\_____                         \n";
    cout << "    _\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\______\\////\\\\\\______\\/\\\\\\_________________\\/\\\\\\_________\\/\\\\\\_____               \n";
    cout << "     _\\/\\\\\\/////////\\\\\\_________\\////\\\\\\___\\//\\\\\\________________\\/\\\\\\_________\\/\\\\\\_____                       \n";
    cout << "      _\\/\\\\\\_______\\/\\\\\\__/\\\\\\______\\//\\\\\\___\\////\\\\\\\\\\\\\\\\\\\\\\_____\\/\\\\\\_________\\/\\\\\\_____          \n";
    cout << "       _\\///________\\///____\\///////////___________\\/////////__\\///////////__\\///////////__                                      \n";
    
    return 0;
}
