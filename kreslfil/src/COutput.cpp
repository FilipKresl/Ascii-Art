#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <assert.h>
#include <ncurses.h>

#include "COutput.hpp"

using namespace std;
COutput::COutput() 
{
    initscr();
    cbreak();
    noecho();
    clear();
    curs_set(0);
}
void COutput::invertPallete()
{
    if ( m_pal % 2 == 0 )
        m_pal ++;
    else
        m_pal --;
}
void COutput::biggerPallete()
{
    if ( m_pal + 2 < m_palletes.size() ) 
        m_pal += 2;
}
void COutput::smallerPallete()
{
    if ( m_pal - 2 < m_palletes.size() ) 
        m_pal -= 2;
}
char COutput::convertAscii ( const int index ) const
{
    int charSize = 256;
    size_t palSize = m_palletes[m_pal].size();
    size_t res = ( (double) m_grays[index] / charSize ) * palSize;
    assert ( res >= 0 && res < palSize );
    return m_palletes[m_pal][res];
}
void COutput::readImg ( CImage * pimg )
{
    m_grays  = pimg->getGrayPixels();
    m_height = pimg->getHeight();
    m_width  = pimg->getWidth();
    m_xShift = 0;
    m_yShift = 0;
}
void COutput::printArt()
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
void COutput::fitStretch()
{
    int newHeight  = LINES;
    int newWidth   = COLS;
    double x_ratio = m_width/(double)newWidth;
    double y_ratio = m_height/(double)newHeight;
    resize ( newHeight, newWidth, x_ratio, y_ratio );
}
void COutput::fitByWidth()
{
    int newWidth   = COLS;
    double x_ratio = m_width/(double)newWidth;
    double y_ratio = x_ratio;
    int newHeight  = m_height / y_ratio;
    resize ( newHeight, newWidth, x_ratio, y_ratio );
}
void COutput::fitByHeight()
{
    int newHeight  = LINES;
    double y_ratio = m_height/(double)newHeight;
    double x_ratio = y_ratio;
    int newWidth   = m_width / x_ratio;
    resize ( newHeight, newWidth, x_ratio, y_ratio );
}
void COutput::fitPerfect()
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
void COutput::moveUp()
{
    if ( m_yShift >= m_height - LINES )
        return;
    m_yShift ++;
}
void COutput::moveDown()
{
    if ( m_yShift <= 0 )
        return;
    m_yShift --;
}
void COutput::moveRight()
{
    if ( m_xShift - 1 <= 0 )
        return;
    m_xShift --;
    m_xShift --;
}
void COutput::moveLeft()
{
    if ( m_xShift - 1 >= m_width - COLS )
        return;
    m_xShift ++;
    m_xShift ++;
}
void COutput::checkShifts()
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
void COutput::lightUp()
{
    int len = m_width * m_height;
    for (int i = 0; i < len; i++)
    {
        m_grays[i] += 15;
        if ( m_grays[i] < 15 ) 
            m_grays[i] = 255;
    }
}
void COutput::lightDown()
{
    int len = m_width * m_height;
    for (int i = 0; i < len; i++)
    {
        m_grays[i] -= 15;
        if ( m_grays[i] > 255 - 15 ) 
            m_grays[i] = 0;
    }
}
void COutput::setResizeMod( const int x )
{
    if ( x >= 0 && x <= 4 )
        m_resizeMode = x;
}
void COutput::setPallete( string palette )
{
    m_palletes.clear();
    m_palletes.push_back( palette );
    m_palletes.push_back( palette );
    m_pal = 0;
}
void COutput::resize ( int newHeight, int newWidth, double x_ratio, double y_ratio ) 
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
vector<uint8_t> COutput::getGrays() const
{
    return m_grays;
}
