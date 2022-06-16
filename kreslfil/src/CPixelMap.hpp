/**
 * @file CPixelMap.hpp
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
    CPixelMap ( const int height, const int width );
    /**
     * @brief stores specific pixel info
     * @param i to which index should be stored
     * @param pix rgba valued pixel
     */
    void setPixels( const int i, const rgba pix );
    /**
     * @brief debug print pixels
     */
    void dumpPixels() const;
    /**
     * @brief convert every colorful pixel to a grayscale one by exact ratio
     */
    void convertToGray();
    /**
     * @brief get the width object
     * @return size_t the width object
     */
    size_t getWidth() const;
    /**
     * @brief get the height object
     * @return size_t the height object
     */
    size_t getHeight() const;
    /**
     * @brief get copy of grayscale pixels of an image
     * @return vector<uint8_t> grayscale pixels of an image
     */
    vector<uint8_t> getGrayPixels() const;
    /**
     * @brief get reference to grayscale pixels of an image
     * @return vector<uint8_t> grayscale pixels of an image
     */
    vector<uint8_t> & getGrayPixelsRef();
    /**
     * @brief set the height object
     * @param newHeight new height of an image
     */
    void setHeight( const int newHeight );
    /**
     * @brief set grayscale pixels of an image
     * @param newGrayPixels new grayscale pixels
     */
    void setGrayPixels( const vector<uint8_t> newGrayPixels );
private:
    size_t m_width;
    size_t m_height;
    vector<rgba> m_pixels;
    vector<uint8_t> m_grayPixels;
};
