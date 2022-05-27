/**
 * @file bmpimage.hpp
 * @brief Implements BMP image loader.
 */

#pragma once

#include <string>
#include "image.hpp"

using namespace std;

/**
 * @brief loads BMP image into the memory.
 */
class CBmpImage : public CImage
{
public:
    /**
     * Create a new CBmpImage object and load specified image from file name.
     * @brief Constructor.
     */
    CBmpImage ( string filename )
    {
    }

};