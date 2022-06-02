/**
 * @file main.cpp
 * @brief Main entry point. 
 */

// clear; g++ -Wall -pedantic main.cpp && ./a.out
// clear; g++ -Wall -pedantic main.cpp -lncurses && ./a.out johnny.bmp

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <assert.h>
#include <ncurses.h>

#define D if(0)

using namespace std;

struct rgba
{
    uint8_t b, g, r, a;
};

class CCommandLine
{
public:
    CCommandLine ( int argc, char** argv )
    {
        m_error = false;
        m_argc = argc;
        m_argv = argv;
        parse();
        // dumpLine();
    }
    ~CCommandLine () {}
    void parse ()
    {
        for (int i = 1; i < m_argc; i++)
        {
            if ( m_argv[i][0] == '-' )
                readCommand( i );
            else
                readImage( i );
        }
    }
    void readImage ( int i )
    {
        string s = "img/";
        s += m_argv[i];
        m_imgs.push_back( s );
    }
    void readCommand ( int i )
    {
        m_commands.push_back( m_argv[i][1] );
        // if ( m_argv[i][1] == '\0' || m_argv[i][2] != '\0' )
        //     m_error = true;
    }
    vector<string> handoverImgs ()
    {
        return m_imgs;
    }
    vector<char> handoverCmds ()
    {
        return m_commands;
    }
    void dumpLine ()
    {
        for (int i = 1; i < m_argc; i++)
        {
            cout << m_argv[i] << endl;
        }
    }
    void dumpIaC ()
    {
        for (int i = 0; i < m_imgs.size(); i++)
        {
            cout << m_imgs[i] << endl;;
        }
        for (int i = 0; i < m_commands.size(); i++)
        {
            cout << m_commands[i] << endl;;
        }
    }
    bool getError ()
    {
        return m_error;
    }

private:
    int             m_argc; 
    char         ** m_argv;
    vector<string>  m_imgs;
    vector<char>    m_commands;
    bool            m_error;
};

class CImage
{
public:
    void init ()
    {
        m_width  = m_buffer[18] + (m_buffer[19] << 8) + (m_buffer[20] << 16) + (m_buffer[21] << 24);
        m_height = m_buffer[22] + (m_buffer[23] << 8) + (m_buffer[24] << 16) + (m_buffer[25] << 24);
        D cout << dec << "size = "   << m_fileSize << endl;
        D cout << dec << "width = "  << m_width    << endl;
        D cout << dec << "height = " << m_height   << endl;
        m_paddingAmount = ((4 - (m_width*3) % 4 ) % 4 );
    }
    void fillPixels ()
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
    // void minimalise ()
    // {
    //     vector<uint8_t> tmp;
    //     for (int h = 0; h < m_height-1; h+=2)
    //     {
    //         for (int w = 0; w < m_width-1; w+=2)
    //         {
    //             int sum = (m_grayVec[h*m_width + w] + m_grayVec[h*m_width + w + 1] + m_grayVec[(h+1)*m_width + w] + m_grayVec[(h+1)*m_width + w + 1]) / 4;
    //             tmp.push_back( sum );
    //         }
    //     }
    //     m_grayVec = tmp;
    //     m_height /= 2;
    //     m_width /= 2;
    // }
    // void maximalise()
    // {
    // }
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
    CImageBMP ( const string & filepath )
    {
        fstream f ( filepath, ios::in | ios::binary );
        if ( !f.is_open () ) 
            throw std::invalid_argument ( "Error: File Not Found." );
        
        int fileHeaderSize = 14;
        vector<uint8_t> fileHeader ( fileHeaderSize );
        f.read ( reinterpret_cast<char*> ( fileHeader.data() ), fileHeaderSize);
        m_fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4]  << 16) + (fileHeader[5]  << 24);
        m_index    = fileHeader[10] + (fileHeader[11] << 8) + (fileHeader[12]  << 16) + (fileHeader[13]  << 24);

        f.seekg ( 0, ios::beg );
        m_buffer.resize(m_fileSize);
        f.read ( reinterpret_cast<char*> ( m_buffer.data() ), m_fileSize);
        f.close();

        init();
        fillPixels();
        convertGray();
        stretch();
    }
};
class CImageTGA : public CImage
{
};
class CImageRAW : public CImage
{
};
class CGallery
{
public:
    CGallery( vector<string> & rpaths) 
    {
        m_index = 0;
        for (int i = 0; i < rpaths.size(); i++)
        {
            string fileExt = getExt( rpaths[i] );
            CImage * p = nullptr;
            if ( fileExt == "bmp" )
            {
                p = new CImageBMP( rpaths[i] );
            }
            else if ( fileExt == "tga" )
            {
                // p = new CImageTGA( rpaths[i] );
            }
            else if ( fileExt == "raw" )
            {
                // p = new CImageRAW( rpaths[i] );
            }
            else 
            {
                throw std::invalid_argument ( "unknown image extension in the command line" );
            }
            m_gallery.push_back( p );
        }
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
    void decIndex()
    {
        m_index --;
        if ( m_index < 0 )
            m_index = m_gallery.size() - 1;
    }
    string getExt( string path )
    {
        size_t i = path.rfind ( '.', path.size() );
        if ( i != string::npos ) 
        {
            return path.substr( i + 1, path.size() - i );
        }
        return string ( "" );
    }
private:
    int             m_index;
    vector<CImage*> m_gallery;
};

class COutput
{
public:
    COutput () 
    {
        initscr();
        cbreak();
        noecho();
        clear();
        fillPallete();
    }
    ~COutput () {}
    void fillPallete ()
    {
        m_palletes.clear();
        m_palletes.push_back( " ." );
        m_palletes.push_back( ". " );
        m_palletes.push_back( " .u0" );
        m_palletes.push_back( "0;. " );
        m_palletes.push_back( "`-_/\\|I" );
        m_palletes.push_back( "I|\\/_-`" );
        m_palletes.push_back( " .;uoC0P@" );
        m_palletes.push_back( "@P0Cou;. " );
        m_pal = 0;
    }
    void invertPallete ()
    {
        if ( m_pal % 2 == 0 )
            m_pal ++;
        else
            m_pal --;

        printArt();
    }
    void biggerPallete ()
    {
        if ( m_pal + 2 < m_palletes.size() ) 
            m_pal += 2;
        printArt();
    }
    void smallerPallete ()
    {
        if ( m_pal - 2 >= 0 ) 
            m_pal -= 2;

        printArt();
    }
    char convertAscii ( int index )
    {
        int charSize = 256;
        int palSize = m_palletes[m_pal].size();
        int res = ( (double) m_grays[index] / charSize ) * palSize;
        assert ( res >= 0 && res < palSize );
        return m_palletes[m_pal][res];
    }
    void readImg ( CImage * pimg )
    {
        m_grays     = pimg->getGrayVec();
        m_height    = pimg->getHeight();
        m_width     = pimg->getWidth();
        m_xShift    = 0;
        m_yShift    = 0;

        printArt();
    }
    void printArt ()
    {
        clear();
        int index = 0;
        for (int i = 0; i < m_height; i++)
        {
            for (int k = 0; k < m_width; k++)
            {
                char c = convertAscii( index + ( m_yShift * m_width ) + m_xShift );
                mvaddch ( i, k, c );
                index ++;
            }
            mvaddch( i, m_width, '\n' );
        }   
        refresh();
    }
    void fitStretch ()
    {
        int newHeight  = LINES;
        int newWidth   = COLS;
        double x_ratio = m_width/(double)newWidth;
        double y_ratio = m_height/(double)newHeight;
        resize ( newHeight, newWidth, x_ratio, y_ratio );
    }
    void fitByWidth ()
    {
        int newWidth   = COLS;
        double x_ratio = m_width/(double)newWidth;
        // double y_ratio = 1;
        // int newHeight  = m_height;
        double y_ratio = x_ratio;
        int newHeight  = m_height / y_ratio;
        resize ( newHeight, newWidth, x_ratio, y_ratio );
    }
    void fitByHeight ()
    {
        int newHeight  = LINES;
        double y_ratio = m_height/(double)newHeight;
        double x_ratio = y_ratio;
        int newWidth   = m_width / x_ratio;
        resize ( newHeight, newWidth, x_ratio, y_ratio );
    }
    void fitPerfect ()
    {
        double x_ratio = m_width/(double)COLS;
        double y_ratio = m_height/(double)LINES;
        
        double xDist = abs ( x_ratio - 1 );
        double yDist = abs ( y_ratio - 1 );
        if ( xDist < yDist )
            fitByWidth();
        else
            fitByHeight();
    }
    void resize ( int newHeight, int newWidth, double x_ratio, double y_ratio ) 
    {
        vector<uint8_t> newGrays;
        newGrays.resize( newWidth * newHeight );
        int x2, y2;
        for (int i = 0; i < newHeight; i++)
        {
            for (int j = 0; j < newWidth; j++) 
            {
                x2 = ( floor ( j * x_ratio ) ) ;
                y2 = ( floor ( i * y_ratio ) ) ;
                newGrays [ ( i * newWidth ) + j ] = m_grays [ ( y2 * m_width ) + x2 ] ;
            }                
        }
        m_width = newWidth;
        m_height = newHeight;
        m_grays = newGrays;   

        printArt();        
    }
    void moveUp ()
    {
        if ( m_yShift >= m_height - LINES )
            return;

        m_yShift ++;
        printArt();
    }
    void moveDown ()
    {
        if ( m_yShift <= 0 )
            return;

        m_yShift --;
        printArt();
    }
    void moveRight ()
    {
        if ( m_xShift - 1 <= 0 )
            return;

        m_xShift --;
        m_xShift --;
        printArt();
    }
    void moveLeft ()
    {
        if ( m_xShift - 1 >= m_width - COLS )
            return;

        m_xShift ++;
        m_xShift ++;
        printArt();
    }
    void checkShifts ()
    {
        if ( m_yShift >= m_height - LINES )
             m_yShift =  m_height - LINES ;
        if ( m_xShift >= m_width  - COLS  )
             m_xShift =  m_width  - COLS  ;
        if ( m_yShift <= 0 )
             m_yShift =  0 ;
        if ( m_xShift <= 0 )
             m_xShift =  0 ;

        printArt();
    }
protected:
    vector<string>  m_palletes; // storing available char for output
    int             m_pal; 
    vector<uint8_t> m_grays;
    int             m_height;
    int             m_width;
    int             m_yShift;
    int             m_xShift;
    // vector<vector<uint8_t> m_grays;
};

class CHexaOutput : public COutput
{

};
class CColorOutput : public COutput
{

};
class CFewAsciiOutput : public COutput
{

};
class CManyAsciiOutput : public COutput
{

};

int main ( int argc, char** argv )
{   
    vector<COutput*> pOutVec;
    pOutVec.push_back ( new COutput          );
    pOutVec.push_back ( new CHexaOutput      );
    pOutVec.push_back ( new CColorOutput     );
    pOutVec.push_back ( new CFewAsciiOutput  );
    pOutVec.push_back ( new CManyAsciiOutput );
    int outIndex = 0;

    CCommandLine cmd( argc, argv );
    vector<string> paths = cmd.handoverImgs();
    CGallery gal ( paths );
    pOutVec[ outIndex ]->readImg ( gal.getImage() );
    pOutVec[ outIndex ]->printArt ();

    bool bContinue = true;
    while ( bContinue )
    {
        char c = tolower ( getch() );
        switch ( c )
        {

        // change the Ascii pallete
        case 'i':
            pOutVec[ outIndex ]->invertPallete();
            break;
        case 'p':
            pOutVec[ outIndex ]->biggerPallete();
            break;
        case 'o':
            pOutVec[ outIndex ]->smallerPallete();
            break;

        // read same/previous/next image
        case 'b':
            pOutVec[ outIndex ]->readImg ( gal.getImage() );
            break;
        case 'm':
            gal.incIndex();
            pOutVec[ outIndex ]->readImg ( gal.getImage() );
            break;
        case 'n':
            gal.decIndex();
            pOutVec[ outIndex ]->readImg ( gal.getImage() );
            break;
        
        // move the image
        case 'w':
            pOutVec[ outIndex ]->moveUp();
            break;
        case 's':
            pOutVec[ outIndex ]->moveDown();
            break;
        case 'd':
            pOutVec[ outIndex ]->moveRight();
            break;
        case 'a':
            pOutVec[ outIndex ]->moveLeft();
            break;
            
        // fit the image in the screen
        case 'z':
            pOutVec[ outIndex ]->fitByHeight();
            break;
        case 'x':
            pOutVec[ outIndex ]->fitByWidth();
            break;
        case 'c':
            pOutVec[ outIndex ]->fitPerfect();
            break;
        case 'v':
            pOutVec[ outIndex ]->fitStretch();
            break;

        // quit
        case 'q':
            bContinue = false;
            break;

        default:
            pOutVec[ outIndex ]->checkShifts();
            break;
        }
    }

    // getch();
    endwin();

    return 0;
}
