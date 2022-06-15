/**
 * @file CFormatTGA.hpp
 * @brief file for derived class CFormatTGA, loads TGA images
 */
#include <string>

#include "CPixelMap.hpp"
#include "CFormat.hpp"
#include "CFlags.hpp"

#pragma once

using namespace std;

/**
 * @brief derived class for loading TGA images
 */
class CFormatTGA : public CFormat
{
    /**
     * @brief loads TGA images
     * @param filename path to the image
     * @param rflags reference to a class containg flags
     * @return CPixelMap containing pixels and essential parametres
     */
    CPixelMap load ( const string & filename, CFlags & rflags ) override;

private:
    void fillPixelMap ( int width, int height, int index, CPixelMap & rpixMap ) override;
};