/**
 * @file COutput.hpp
 * @brief (base) COutput, (derived) COutputRound, (derived) COutputSharp, CMessages
 */
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <assert.h>
#include <ncurses.h>

#include "CImage.hpp"

#pragma once

using namespace std;
/**
 * @brief base class for editing of the image-output
 */
class COutput
{
public:
    /**
     * @brief Construct a new COutput object
     */
    COutput() 
    {
        initscr();
        cbreak();
        noecho();
        clear();
        curs_set(0);
        m_resizeMode = 0;
    }
    virtual ~COutput () {}
    /**
     * @brief pure virtual method for initializing the pallete
     */
    virtual void fillPallete() = 0;
    /**
     * @brief selects inverted pallete
     */
    void invertPallete()
    {
        if ( m_pal % 2 == 0 )
            m_pal ++;
        else
            m_pal --;

    }
    /**
     * @brief selects larger pallete
     */
    void biggerPallete()
    {
        if ( m_pal + 2 < m_palletes.size() ) 
            m_pal += 2;
    }
    /**
     * @brief selects larger pallete
     */
    void smallerPallete()
    {
        if ( m_pal - 2 >= 0 ) 
            m_pal -= 2;
    }
    /**
     * @brief for a grayscale 8-bit number finds a suitable Ascii char from pallete
     * 
     * @param index which 8-bit number from a member vector should be converted
     * @return char the converted Ascii char
     */
    char convertAscii ( int index )
    {
        int charSize = 256;
        size_t palSize = m_palletes[m_pal].size();
        size_t res = ( (double) m_grays[index] / charSize ) * palSize;
        assert ( res >= 0 && res < palSize );
        return m_palletes[m_pal][res];
    }
    /**
     * @brief initializes member variables for a new image
     * 
     * @param pimg pointer to a current image
     */
    void readImg ( CImage * pimg )
    {
        m_grays  = pimg->getGrayVec();
        m_height = pimg->getHeight();
        m_width  = pimg->getWidth();
        m_xShift = 0;
        m_yShift = 0;
    }
    /**
     * @brief prints the image via ncurses
     */
    virtual void printArt()
    {
        if      ( m_resizeMode == 1 )
            fitByHeight();
        else if ( m_resizeMode == 2 )
            fitByWidth();
        else if ( m_resizeMode == 3 )
            fitPerfect();
        else if ( m_resizeMode == 4 )
            fitStretch();
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
    /**
     * @brief stretches the image to fit to entire screen and be all-visible
     * temporarily damages the image-ratio
     */
    void fitStretch()
    {
        int newHeight  = LINES;
        int newWidth   = COLS;
        double x_ratio = m_width/(double)newWidth;
        double y_ratio = m_height/(double)newHeight;
        resize ( newHeight, newWidth, x_ratio, y_ratio );
    }
    /**
     * @brief resizes the images to fit to the screen by width, doesn't care about height
     */
    void fitByWidth()
    {
        int newWidth   = COLS;
        double x_ratio = m_width/(double)newWidth;
        // double y_ratio = 1;
        // int newHeight  = m_height;
        double y_ratio = x_ratio;
        int newHeight  = m_height / y_ratio;
        resize ( newHeight, newWidth, x_ratio, y_ratio );
    }
    /**
     * @brief resizes the images to fit to the screen by height, doesn't care about width
     */
    void fitByHeight()
    {
        int newHeight  = LINES;
        double y_ratio = m_height/(double)newHeight;
        double x_ratio = y_ratio;
        int newWidth   = m_width / x_ratio;
        resize ( newHeight, newWidth, x_ratio, y_ratio );
    }
    /**
     * @brief decides if fitByWidth() or fitByHeight() should be called
     */
    void fitPerfect()
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
    /**
     * @brief moves the image up
     */
    void moveUp()
    {
        if ( m_yShift >= m_height - LINES )
            return;

        m_yShift ++;
    }
    /**
     * @brief moves the image down
     */
    void moveDown()
    {
        if ( m_yShift <= 0 )
            return;

        m_yShift --;
    }
    /**
     * @brief moves the image right
     */
    void moveRight()
    {
        if ( m_xShift - 1 >= m_width - COLS )
            return;

        m_xShift ++;
        m_xShift ++;
    }
    /**
     * @brief moves the image left
     */
    void moveLeft()
    {
        if ( m_xShift - 1 <= 0 )
            return;

        m_xShift --;
        m_xShift --;
    }
    /**
     * @brief checks if the image has not reached permitted screen borders
     */
    void checkShifts()
    {
        if ( m_yShift >= m_height - LINES )
             m_yShift =  m_height - LINES ;
        if ( m_xShift >= m_width  - COLS  )
             m_xShift =  m_width  - COLS  ;
        if ( m_yShift <= 0 )
             m_yShift =  0 ;
        if ( m_xShift <= 0 )
             m_xShift =  0 ;
    }
    /**
     * @brief lightens every pixel
     */
    void lightUp()
    {
        int len = m_width * m_height;
        for (int i = 0; i < len; i++)
        {
            m_grays[i] += 15;
            if ( m_grays[i] < 15 ) 
                m_grays[i] = 255;
        }
    }
    /**
     * @brief darkens every pixel
     */
    void lightDown()
    {
        int len = m_width * m_height;
        for (int i = 0; i < len; i++)
        {
            m_grays[i] -= 15;
            if ( m_grays[i] > 255 - 15 ) 
                m_grays[i] = 0;
        }
    }
    /**
     * @brief sets which resize method should be called automatically to every image
     * @param x index to which resize mode is active
     */
    void setResizeMod( int x )
    {
        if ( x >= 0 && x <= 4 )
            m_resizeMode = x;
    }
    /**
     * @brief sets own pallete
     * 
     * @param palette new pallete
     */
    void setPallete( string palette )
    {
        m_palletes.clear();
        m_palletes.push_back( palette );
        m_palletes.push_back( palette );
        m_pal = 0;
    }
protected:
    /**
     * @brief resizes the image, keeps the right ratio
     * 
     * @param newHeight new height of the image
     * @param newWidth new width of the image
     * @param x_ratio ratio betwenn current image-width and screen-width
     * @param y_ratio ratio betwenn current image-height and screen-height
     */
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
    }
protected:
    vector<string>  m_palletes;
    size_t          m_pal; 
    vector<uint8_t> m_grays;
    int             m_height;
    int             m_width;
    int             m_yShift;
    int             m_xShift;
    int             m_resizeMode;
};

/**
 * @brief derived class for output in round shapes
 */
class COutputRound : public COutput
{
    /**
     * @brief initializes the pallete
     */
    virtual void fillPallete()
    {
        m_palletes.clear();
        m_palletes.push_back( " o" );
        m_palletes.push_back( "o " );
        m_palletes.push_back( " .oO80" );
        m_palletes.push_back( "08Oo. " );
        m_pal = 0;
    }
};

/**
 * @brief derived class for output in sharp shapes
 */
class COutputSharp : public COutput
{
    /**
     * @brief initializes the pallete
     */
    virtual void fillPallete ()
    {
        m_palletes.clear();
        m_palletes.push_back( " -" );
        m_palletes.push_back( "- " );
        m_palletes.push_back( " ,-/" );
        m_palletes.push_back( "/-, " );
        m_palletes.push_back( "`-_/\\|I" );
        m_palletes.push_back( "I|\\/_-`" );
        m_pal = 0;
    }
};

// class COutputColor : public COutput
// {
// };

// other derived classes ...

/**
 * @brief class for printing nonpicture output 
 */
class CMessages
{
public:
    /**
     * @brief initializes the screen for ncurses output
     */
    void ncursInit()
    {
        initscr();
        cbreak();
        noecho();
    }
    /**
     * @brief prints help manual if the user asks for it 
     */
    void printHelp()
    {
        ncursInit();
        printw ( "--HELP-- \n" );
        printw ( "commands: \n" );
        printw ( "  -h for help \n" );
        printw ( "  -p for play \n" );
        printw ( "  -l for inserting own pallete in a file (write the name of the file before the images) \n" );
        printw ( "  -n for natural look - initial stretching disabled \n" );
        printw ( "  -r for output in round Ascii (e.g. o80@) (default) \n" );
        printw ( "  -s for output in sharp Ascii (e.g. -/I#) \n\n" );
        printw ( "examples: \n" );
        printw ( "  ./a.out img/johnny.bmp \n" );
        printw ( "  ./a.out img/albert.tga \n" );
        printw ( "  ./a.out -l palleteNumbers.txt img/cat2.bmp img/cat.bmp \n" );
        printw ( "  ./a.out -l palletePerfect.txt img/cat2.bmp img/cat.bmp \n" );
        printw ( "  ./a.out -s -p img/img*.bmp \n\n" );
        printw ( "editing: \n" );
        printw ( "  Z,X,C,V for different types of RESIZING \n" );
        printw ( "  N,M     for SWITCHING between images \n" );
        printw ( "  B       for RELOADING the image with initial setting \n" );
        printw ( "  K,L     for increasing/decreasing LIGHT for the current image \n" );
        printw ( "  W,A,S,D for MOVING the current image \n" );
        printw ( "  F       for DELETING the image \n" );
        printw ( "  G,H     for SWAPPING the image with previous/next one \n" );
        printw ( "  I       for INVERTING the colors \n" );
        printw ( "  O,P     for changing the PALLETE \n" );
        printw ( "  U       for PLAY/STOP \n" );
        printw ( "  Y       for changing the Direction of playing \n" );
        
        refresh();
        endwin();
    }
    /**
     * @brief prints the error message if incorrect input detected 
     */
    void printError()
{        
    ncursInit();
    printw( "--WRONG INPUT--\n" );
    printw( "type:\n" );
    printw( "   ./a.out -h\n" );
    printw( "for help\n" );
    refresh();
    endwin();
}
};

