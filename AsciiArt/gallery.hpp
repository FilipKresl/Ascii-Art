/**
 * @file gallery.hpp
 * @brief Manages multiple images.
 * Gallery contains multiple images and enables to cycle through them or select specific image and move it.
 */

#pragma once

#include <vector>
#include <string>
#include "image.hpp"

using namespace std;

typedef std::vector< CImage * > vecImages;

/**
 * @brief Contains multiple images and methods to manipulate with them.
 */
class CGallery
{
public:
    /**
     * Create a new CGallery object.
     * @brief Constructor.
     */
    virtual ~CGallery ( )
    {
        clear ();        
    }

    /**
     * @brief Enables adding different types of images to gallery (using polymorphism).
     * @param imageNames Vector of names of the images to be added. 
     */
    void addImages ( const std::vector<std::string> & imageNames )
    {
        for ( size_t i = 0, size = imageNames . size(); i < size; i++)
        {
            std::string fileName = imageNames[ i ];
            std::string fileExt = getExt ( fileName );

            if ( fileExt == "bmp" )
            {
                // tbd - add an instace of CBmpImage
            }
            else if ( fileExt == "tga" )
            {
                // tbd - add an instace of CTgaImage
            }
            else if ( fileExt == "raw" )
            {
                // tbd - add an instace of CRawImage
            }
            else 
            {
                throw std::invalid_argument ( "unknown image extension in the command line" );
            }
        }   
    }
    /**
     * @brief 
     * 
     * @param atIndex Index to the image to be erased.
     * @return true If erasion successful.
     * @return false If either empty gallery or index out of range
     */
    bool erase ( size_t atIndex )
    {
        if ( m_images.size() >= 0 && atIndex <= m_images.size() - 1 )
        {
            delete m_images [ atIndex ];
            m_images.erase ( m_images.begin() + atIndex );
            return true;
        }
        return false;
    }

    /**
     * @brief Clears the whole image array (gallery) and frees the allocated memory
     */
    void clear ( )
    {
        for ( size_t i = 0, size = m_images.size(); i < size; i++)
        {
            delete m_images [ i ];
        }
        m_images.clear ();
    }

    /**
     * @brief Moves the image to the front of gallery.
     * @param atIndex Index to the image that should be moved.
     * @return true If successful.
     * @return false If there is less than 2 instances in the gallery.
     */
    bool moveForwards ( size_t atIndex )
    {
        // if ( m_images.size() >= 2 && atIndex < m_images.size() - 1 )
        // {
        //     move ( m_images, atIndex, atIndex + 1 );
        //     return true;
        // }
        size_t size = m_images.size();
        if ( m_images.size() > 1 )
        {
            move ( m_images, atIndex, ( atIndex + 1 ) % size );
            return true;
        }
        return false;
    }

    /**
     * @brief Moves the image to the back of gallery.
     * @param atIndex Index to the image that should be moved.
     * @return true If successful.
     * @return false If there is less than 2 instances in the gallery.
     */
    bool moveBackwards ( size_t atIndex )
    {
        size_t size = m_images.size();
        if ( size > 1 )
        {
            move ( m_images, atIndex, ( atIndex - 1 + size ) % size );
            return true;
        }
        return false;
    }
private:
    /**
     * @brief Swaps two objects specified by given indices.
     * @tparam t Template parameter.
     * @param v Vector of images.
     * @param oldIndex Old index.
     * @param newIndex New index.
     */
    template <typename t> void move(std::vector<t>& v, size_t oldIndex, size_t newIndex)
    {
        if (oldIndex > newIndex)
            std::rotate(v.rend() - oldIndex - 1, v.rend() - oldIndex, v.rend() - newIndex);
        else        
            std::rotate(v.begin() + oldIndex, v.begin() + oldIndex + 1, v.begin() + newIndex + 1);
    }

    /**
     * @brief Parse extension from the filename.
     * @param fileName Name of given file.
     * @return std::string extension.
     */
    std::string getExt( std::string fileName )
    {
        size_t i = fileName.rfind ( '.', fileName.length () );
        if ( i != std::string::npos ) 
        {
            return fileName.substr( i + 1, fileName.length() - i );
        }

        return std::string ( "" );
    }

private:
    vecImages m_images;
};