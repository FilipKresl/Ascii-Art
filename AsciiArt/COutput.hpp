#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <ncurses.h>

#include "CImage.hpp"

#pragma once

#define D if(0)

using namespace std;

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
    void lightUp()
    {
        int len = m_width * m_height;
        for (int i = 0; i < len; i++)
        {
            m_grays[i] += 15;
            if ( m_grays[i] < 15 ) 
                m_grays[i] = 255;
        }
        printArt();
    }
    void lightDown()
    {
        int len = m_width * m_height;
        for (int i = 0; i < len; i++)
        {
            m_grays[i] -= 15;
            if ( m_grays[i] > 255 - 15 ) 
                m_grays[i] = 0;
        }
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
