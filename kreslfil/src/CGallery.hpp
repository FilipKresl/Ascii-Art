/**
 * @file CGallery.hpp
 * @brief file for class CGallery, manages CImages
 */
#include "CFormatManager.hpp"
#include "CImage.hpp"
#include "CFlags.hpp"

#pragma once

/**
 * @brief class for storing and managing images
 */
class CGallery
{
public:
    /**
     * @brief construct a new CGallery object
     * @param paths contains paths to every given image
     * @param rflags reference to a class containg flags
     */
    CGallery( vector<string> & paths, CFlags & rflags );
    /**
     * @brief destroy the CGallery object
     */
    ~CGallery();
    /**
     * @brief increases m_index -> moves to next image
     */
    void incIndex();
    /**
     * @brief decreases m_index -> moves to previous image
     */
    void decIndex();
    /**
     * @brief erase current image
     */    
    void deleteImg();
    /**
     * @brief swapps current images with the next one
     */
    void moveImgForward();
    /**
     * @brief swapps current images with the previous one
     */
    void moveImgBack();
    /**
     * @brief getter for specifiic image by m_index
     */
    CImage * getImage();
private:
    size_t m_index;
    vector<CImage  *> m_images;
};