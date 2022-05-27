/**
 * @file image.hpp
 * @brief Implements basic image.
 * Keeps the info (color + alpha) about pixels of the image in vector.
 * Contains functions useful for manipulation of the image (resize(), flip(), invert(),...).
 */

#pragma once

#include <vector>

using namespace std;
/**
 * @brief Access pixel either as uint_32 or as four rgba bytes.
 */
union t_pixel 
{
    std::uint32_t color;
    struct 
    {
        std::uint8_t b, g, r, a;

    } rgba;
};

/**
 * @brief Keeps in memory data about BMP/TGA/RAW/... images.
 */
class CImage
{
public:
    /**
     * Create a new CImage object.
     * @brief Constructor.
     * @param width The width of the image.
     * @param height The height of the image.
     */
    CImage ( size_t width, size_t height )
    {
        init ( width, height );
    }

    /**
     * Will be overloaded by derived classes.
     * @brief Constructor.
     */
    CImage ( string filename )
    {
    }

    /**
     * @brief Initializes image, called in constructor.
     * @param width The width of the image.
     * @param height The height of the image.
     */
    void init ( int width, int height )
    {
        m_width = width;
        m_height = height;
        m_bitsPerPixel = 32;
        m_pixels.resize ( width * height );    
    }

    /**
     * @brief Resizes the image to fit different scales.
     * @param newWidth New width of the image.
     * @param newHeight New height of the image.
     */
     void resize ( size_t newWidth, size_t newHeight )
    {
        // tbd

        m_width = newWidth;
        m_height = newHeight;
    }

    /**
     * @brief Inverts the color scheme of image by storing complements of rgba values to 0xff.
     */
    void invert ()
    {
        std::vector<t_pixel> tmpPixels = m_pixels;
        for ( size_t y = 0; y < m_height; y++ )
        {
            for ( size_t x = 0; x < m_width; x++ )
            {
                int index = y * m_width + x; 
                m_pixels[index].rgba.r = 255 - tmpPixels[index].rgba.r;
                m_pixels[index].rgba.g = 255 - tmpPixels[index].rgba.g;
                m_pixels[index].rgba.b = 255 - tmpPixels[index].rgba.b;
                m_pixels[index].rgba.a = tmpPixels[index].rgba.a;
            }
        }
    }
    /**
     * @brief Flips the image by Y axis.
     */
    void flipVertical ()
    {
        std::vector<t_pixel> tmpPixels = m_pixels;
        for ( size_t y = 0; y < m_height; y++ )
        {
            for ( size_t x = 0; x < m_width; x++ )
            {
                m_pixels[y * m_width + x] = tmpPixels[(m_height - 1 - y) * m_width + x];
            }
        }
    }

    /**
     * @brief Flips the image by X axis.
     */
    void flipHorizontal ()
    {
        std::vector<t_pixel> tmpPixels = m_pixels;
        for ( size_t y = 0; y < m_height; y++ )
        {
            for ( size_t x = 0; x < m_width; x++ )
            {
                m_pixels[y * m_width + x] = tmpPixels[y * m_width + m_width - 1 - x];
            }
        }
    }
/**
 * Width of image.
 * Height of image.
 * How many bits per pixel (using 32 because of the rgba format).
 * Vector of struct t_pixel, used as a conteiner for keeping in memory the image.
 */
protected:
    size_t          m_width;
    size_t          m_height;
    short int       m_bitsPerPixel;
    vector<t_pixel> m_pixels;
};