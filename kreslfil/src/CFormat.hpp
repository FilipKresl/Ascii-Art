/**
 * @file CFormat.hpp
 * @brief file for class CFormat, base class for loading images from a file
 */
#include <vector>

#include "rgba.hpp"
#include "CPixelMap.hpp"
#include "CFlags.hpp"

#pragma once

using namespace std;
/**
 * @brief base class for loading images from a file
 */
class CFormat
{
public:
    /**
     * @brief destroy the CFormat object
     */
    virtual ~CFormat() {}
    /**
     * @brief loads image from a file to CPixelMap
     * @param filename path to the image
     * @param rflags reference to a class containg flags
     * @return CPixelMap containing pixels and essential parametres
     */
    virtual CPixelMap load ( const string & filename, CFlags & rflags ) = 0;
protected:
    virtual void fillPixelMap ( int width, int height, int index, CPixelMap & rpixMap ) = 0;
    void stretch( CPixelMap & rpixMap ) const;
    vector<uint8_t> m_buffer;
};