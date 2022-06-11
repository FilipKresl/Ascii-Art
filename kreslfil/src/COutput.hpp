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
class COutput
{
public:
    COutput();
    virtual ~COutput () {}
    virtual void fillPallete() = 0;
    void invertPallete();
    void biggerPallete();
    void smallerPallete();
    char convertAscii ( int index );
    void readImg ( CImage * pimg );
    virtual void printArt();
    void fitStretch();
    void fitByWidth();
    void fitByHeight();
    void fitPerfect();
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void checkShifts();
    void lightUp();
    void lightDown();
    void setResizeMod( int x );
    void setPallete( string palette );
    
protected:
    void resize ( int newHeight, int newWidth, double x_ratio, double y_ratio );
    vector<string>  m_palletes;
    size_t          m_pal; 
    vector<uint8_t> m_grays;
    int             m_height;
    int             m_width;
    int             m_yShift;
    int             m_xShift;
    int             m_resizeMode;
};
