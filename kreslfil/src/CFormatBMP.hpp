/**
 * @file CFormatBMP.hpp
 * @brief file for derived class CFormatBMP, loads BMP images
 */
#include "CPixelMap.hpp"
#include "CFormat.hpp"
#include "CFlags.hpp"

#pragma once

using namespace std;

/**
 * @brief derived class for loading BMP images
 */
class CFormatBMP : public CFormat
{
public:
    /**
     * @brief loads BMP images
     * @param filename path to the image
     * @param rflags reference to a class containg flags
     * @return CPixelMap containing pixels and essential parametres
     */
    CPixelMap load ( const string & filename, CFlags & rflags ) override;
    
private:
    void fillPixelMap ( const int width, const int height, int index, CPixelMap & rpixMap ) override;
};
