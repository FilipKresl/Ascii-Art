/**
 * @file CGallery.hpp
 * @brief CGallery
 */
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <fstream>

#include "CImage.hpp"

#pragma once

using namespace std;

/**
 * @brief Class for storing and managing images
 */
class CGallery
{
public:
    /**
     * @brief destructor for allocated images 
     */
    ~CGallery() 
    {
        for (int i = 0; i < m_gallery.size(); i++)
        {
            delete m_gallery[i];
        }
    }
    /**
     * @brief for each image decides by it's extension which COutput derived class should be made
     * 
     * @param rpaths vector containing paths of all images
     * @param bdoStretch if images should be stretched or keep natural look
     */
    void init ( vector<string> & rpaths, bool bdoStretch ) 
    {
        m_index = 0;
        for (int i = 0; i < rpaths.size(); i++)
        {
            string fileExt = getExt( rpaths[i] );
            CImage * p = nullptr;
            if ( fileExt == "bmp" )
            {
                p = new CImageBMP ();
                p->loadImg( rpaths[i], bdoStretch );
            }
            else if ( fileExt == "tga" )
            {
                p = new CImageTGA ();
                p->loadImg( rpaths[i], bdoStretch );
            }
            // else if ( fileExt == "raw" )
            // {
            //     p = new CImageRAW ();
            //     p->loadImg( rpaths[i], bdoStretch );
            // }
            // // ...
            else 
            {
                throw invalid_argument ( "unknown image extension in the command line" );
            }
            m_gallery.push_back( p );
        }
    }
    /**
     * @brief Getter for specifiic image by m_index
     */
    CImage * getImage()
    {
        return m_gallery[m_index];
    }
    /**
     * @brief increases m_index -> move to next image
     */
    void incIndex()
    {
        m_index ++;
        if ( m_index >= m_gallery.size() )
            m_index = 0;
    }
    /**
     * @brief decreases m_index -> move to previous image
     */
    void decIndex()
    {
        m_index --;
        if ( m_index < 0 )
            m_index = m_gallery.size() - 1;
    }

    /**
     * @brief erase current image
     */
    void deleteImg()
    {
        vector<CImage*>::iterator it;
        it = m_gallery.begin();
        it += m_index;
        CImage * p = m_gallery[m_index];
        if ( m_gallery.size() > 1 )
        {
            m_gallery.erase( it );
            if ( m_index >= m_gallery.size() )
                m_index = 0;
            delete p;
        }
    }
    /**
     * @brief swapps current images with the next one
     */
    void moveImgForward()
    {
        if ( m_gallery.size() > 1 )
        {
            int indexNext = m_index + 1;
            if ( indexNext >= m_gallery.size() )
                indexNext = 0;
            CImage * p = m_gallery[ m_index ];
            m_gallery[ m_index ] = m_gallery[ indexNext ];
            m_gallery[ indexNext ] = p;
        }
    }
    /**
     * @brief swapps current images with the previous one
     */
    void moveImgBack()
    {
        if ( m_gallery.size() > 1 )
        {
            int indexPrev = m_index - 1;
            if ( indexPrev < 0 )
                indexPrev = m_gallery.size() - 1;
            CImage * p = m_gallery[ m_index ];
            m_gallery[ m_index ] = m_gallery[ indexPrev ];
            m_gallery[ indexPrev ] = p;
        }
    }
    /**
     * @brief getter for amount of images
     */
    size_t size()
    {
        return m_gallery.size();
    }
private:
    /**
     * @brief reads the postfix (extension) of a image
     * 
     * @param path path to a image
     * @return extension as a string 
     */
    string getExt( string path )
    {
        size_t i = path.rfind ( '.', path.size() );
        if ( i != string::npos ) 
        {
            return path.substr( i + 1, path.size() - i );
        }
        return string ( "" );
    }
private:
    int             m_index;
    vector<CImage*> m_gallery;
};
