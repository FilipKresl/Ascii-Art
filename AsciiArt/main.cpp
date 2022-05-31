/**
 * @file main.cpp
 * @brief Main entry point. 
 */

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <fstream>
#include <assert.h>
#include <ncurses.h>

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
    void stretch()
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
    void dumpGrayVec()
    {
        cout << "grayVec:" << endl;
        for (int i = 0; i < m_grayVec.size(); i++)
        {
            cout << hex << (int) m_grayVec[i] << " | ";
        }
        cout << endl; 
    }
    int getHeight()
    {
        return m_height;
    }
    int getWidth()
    {
        return m_width;
    }
    vector<uint8_t> getGrayVec()
    {
        return m_grayVec;
    }
private:
    int             m_fileSize;
    int             m_width;
    int             m_height;
    vector<uint8_t> m_buffer; // storing raw input
    int             m_index; // where to read from m_buffer
    vector<rgba>    m_pixels; // storing rgba pixels
    int             m_paddingAmount;
    vector<uint8_t> m_grayVec; // storing 8bit average for each pixel
};

class CGallery
{
public:
    CGallery( vector<string> & rpaths) 
    {
        for (int i = 0; i < rpaths.size(); i++)
        {
            CImage * p = new CImage( rpaths[i] );
            m_gallery.push_back( p );
        }
        m_index = 0;
    }
    ~CGallery() 
    {
        for (int i = 0; i < m_gallery.size(); i++)
        {
            delete m_gallery[i];
        }
    }
    CImage * getImage()
    {
        return m_gallery[m_index];
    }
    void incIndex()
    {
        m_index ++;
        if ( m_index >= m_gallery.size() )
            m_index = 0;
    }

private:
    int             m_index;
    vector<CImage*> m_gallery;
};

class COutput
{
public:
    COutput() 
    {
        initscr();
        cbreak();
        noecho();
        clear();

        // printMenu();
        fillPallete();
    }
    ~COutput() {}
    // void printMenu()
    // {
    // }
    void fillPallete()
    {
        m_palletes.clear();
        m_palletes.push_back( " ." );
        m_palletes.push_back( ". " );
        m_palletes.push_back( " .u0" );
        m_palletes.push_back( "0;. " );
        m_palletes.push_back( " .;uoC0P@" );
        m_palletes.push_back( "@P0Cou;. " );
        m_palletes.push_back( "  .,:;iucowCOD0P8@" );
        m_palletes.push_back( "@8P0DOCwocui;:,.  " );
        m_pal = 0;
    }
    void invertPallete()
    {
        if ( m_pal % 2 == 0 )
            m_pal ++;
        else
            m_pal --;
    }
    void biggerPallete()
    {
        if ( m_pal + 2 < m_palletes.size() ) 
            m_pal += 2;
    }
    void smallerPallete()
    {
        if ( m_pal - 2 >= 0 ) 
            m_pal -= 2;
    }
    char convertAscii( int index )
    {
        int charSize = 256;
        int palSize = m_palletes[m_pal].size();
        int res = ( (double) m_grays[index] / charSize ) * palSize;
        assert ( res >= 0 && res < palSize );
        return m_palletes[m_pal][res];
    }
    void printArt( CImage * pimg )
    {
        m_grays     = pimg->getGrayVec();
        int height  = pimg->getHeight();
        int width   = pimg->getWidth();
        int index   = 0;
        for (int i = 0; i < height; i++)
        {
            for (int k = 0; k < width; k++)
            {
                char c = convertAscii( index );
                mvaddch ( i, k, c );
                index ++;
            }
            mvaddch( i, width, '\n' );
        }   
        refresh();
    }

private:
    vector<string>  m_palletes; // storing available char for output
    int             m_pal; 
    vector<uint8_t> m_grays;
};
// class CCommandLine
// {
// public:
//     CCommandLine( int argc, char** argv )
//     {
//     }
// private:
// };
// clear; g++ -Wall -pedantic main.cpp && ./a.out
// clear; g++ -Wall -pedantic main.cpp -lncurses && ./a.out

int main ( int argc, char** argv )
{   
    vector<string> paths;
    paths.push_back( "img/img0.bmp" );
    paths.push_back( "img/img1.bmp" );
    paths.push_back( "img/img2.bmp" );
    paths.push_back( "img/img3.bmp" );
    paths.push_back( "img/img4.bmp" );
    paths.push_back( "img/img5.bmp" );
    paths.push_back( "img/img6.bmp" );
    paths.push_back( "img/img7.bmp" );
    CGallery gal ( paths );

    // CImage img ( path );
    
    COutput out;
    out.printArt ( gal.getImage() );

    bool bContinue = true;
    while ( bContinue )
    {
        char c = tolower ( getch() );
        switch ( c )
        {
        case 'i':
            out.invertPallete();
            clear();
            out.printArt( gal.getImage() );
            break;
        case 'p':
            out.biggerPallete();
            clear();
            out.printArt( gal.getImage() );
            break;
        case 'o':
            out.smallerPallete();
            clear();
            out.printArt( gal.getImage() );
            break;
        case 'm':
            gal.incIndex();
            out.printArt( gal.getImage() );
            break;
        case 'n':
            // previous
            break;
        case 'q':
            bContinue = false;
            break;
        default:
            refresh();
            break;
        }
    }

    getch();
    endwin();

    return 0;
}
