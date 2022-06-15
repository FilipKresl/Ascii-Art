/**
 * @file CImage.hpp
 * @brief file for class CImage, info about specific image
 * 
 */
#include "CPixelMap.hpp"

using namespace std;

#pragma once

/**
 * @brief contains pixels of an image + essential parametres
 */
class CImage
{
public:
    /**
     * @brief construct a new CImage object
     * @param pixMap pixels of an image + essential parametres
     */
    CImage( CPixelMap pixMap );
    /**
     * @brief debug print pixels
     */
    void dumpPixels();
    /**
     * @brief get the width of an image
     * @return size_t width of an image
     */
    size_t getWidth();
    /**
     * @brief get the height of an image
     * @return size_t height of an image
     */
    size_t getHeight();
    /**
     * @brief give access to grayscale pixels of an image
     * @return vector<uint8_t> containing pixels translated to grayscale values
     */
    vector<uint8_t> getGrayPixels();

protected:
    size_t m_width;
    size_t m_height;
    vector<uint8_t> m_grayPixels;
};