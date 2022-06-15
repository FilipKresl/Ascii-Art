/**
 * @file COutput.hpp
 * @brief file for base class COutput, manages art output
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
 * @brief class for managing output effects
 */
class COutput
{
public:
    /**
     * @brief construct a new COutput object
     */
    COutput();
    /**
     * @brief destroy the COutput object
     */
    virtual ~COutput () {}
    /**
     * @brief initiates pallete for printing output
     */
    virtual void fillPallete() = 0;
    /**
     * @brief inverts pallete
     */
    void invertPallete();
    /**
     * @brief enlarges pallete to pre-specified pallete
     */
    void biggerPallete();
    /**
     * @brief compresse pallete to pre-specified pallete
     */
    void smallerPallete();
    /**
     * @brief converts pixel to char from pallete
     * @param index which pixel should be read
     * @return char converted ascii-char ready for printing 
     */
    char convertAscii ( int index );
    /**
     * @brief reads and stores values of an image for faster manipulation of effects
     * @param pimg pointer to an image
     */
    void readImg ( CImage * pimg );
    /**
     * @brief prints converted chars on screen
     */
    virtual void printArt();
    /**
     * @brief stretches image to the screen, damages ratio
     */
    void fitStretch();
    /**
     * @brief stretches image to fit by width, keeps ratio
     */
    void fitByWidth();
    /**
     * @brief stretches image to fit by height, keeps ratio
     */
    void fitByHeight();
    /**
     * @brief chooses between fitByWidth() and fitByHeight()
     */
    void fitPerfect();
    /**
     * @brief which resize method should be called every time
     * @param x key to specific resize method
     */
    void setResizeMod( int x );
    /**
     * @brief moves the image up by 1 pixel
     */
    void moveUp();
    /**
     * @brief moves the image down by 1 pixel
     */
    void moveDown();
    /**
     * @brief moves the image to the right by 2 pixels
     */
    void moveRight();
    /**
     * @brief moves the image to the left by 2 pixels
     */
    void moveLeft();
    /**
     * @brief checks that the is in it's boundaries 
     * called when nonrecognized key is pressed
     * useful when resizing the terminal window
     */
    void checkShifts();
    /**
     * @brief lightens the whole image
     */
    void lightUp();
    /**
     * @brief darkens the whole image
     */
    void lightDown();
    /**
     * @brief set user's pallete
     * @param palette string containg chars for output print
     */
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
