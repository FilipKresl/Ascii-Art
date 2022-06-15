/**
 * @file CPixelMap.cpp
 * @brief file for class CPixelMap that contains data of an image
 */
#include <iostream>
#include <vector>
#include <iomanip>

#include "rgba.hpp"

#pragma once

using namespace std;

/**
 * @brief class for storing pixels and essential parametres of an image while loading
 */
class CPixelMap
{
public:
    /**
     * @brief construct a new CPixelMap object
     * @param height height of an image
     * @param width width of an image
     */
    CPixelMap ( int height, int width );
    /**
     * @brief stores specific pixel info
     * @param i to which index should be stored
     * @param pix rgba valued pixel
     */
    void setPixels( int i, rgba pix );
    /**
     * @brief debug print pixels
     */
    void dumpPixels();
    /**
     * @brief convert every colorful pixel to a grayscale one by exact ratio
     */
    void convertToGray();
    /**
     * @brief get the width object
     * @return size_t the width object
     */
    size_t getWidth();
    /**
     * @brief get the height object
     * @return size_t the height object
     */
    size_t getHeight();
    /**
     * @brief get copy of grayscale pixels of an image
     * @return vector<uint8_t> grayscale pixels of an image
     */
    vector<uint8_t> getGrayPixels();
    /**
     * @brief get reference to grayscale pixels of an image
     * @return vector<uint8_t> grayscale pixels of an image
     */
    vector<uint8_t> & getGrayPixelsRef();
    /**
     * @brief set the height object
     * @param newHeight new height of an image
     */
    void setHeight( int newHeight );
    /**
     * @brief set grayscale pixels of an image
     * @param newGrayPixels new grayscale pixels
     */
    void setGrayPixels( vector<uint8_t> newGrayPixels );
private:
    size_t m_width;
    size_t m_height;
    vector<rgba> m_pixels;
    vector<uint8_t> m_grayPixels;
};
