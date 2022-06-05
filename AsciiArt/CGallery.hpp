#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <fstream>

#include "CImage.hpp"

#pragma once

using namespace std;

class CGallery
{
public:
    CGallery( vector<string> & rpaths, bool bdoStretch) 
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
            else if ( fileExt == "raw" )
            {
            //  p = new CImageRAW ( rpaths[i] );
            }
            else 
            {
                throw invalid_argument ( "unknown image extension in the command line" );
            }
            m_gallery.push_back( p );
        }
    }
    ~CGallery() 
    {
        for (int i = 0; i < m_gallery.size(); i++)
        {
            delete m_gallery[i];
        }
    }
    CImage * getImage()
    {
        return m_gallery[m_index];
    }
    void incIndex()
    {
        m_index ++;
        if ( m_index >= m_gallery.size() )
            m_index = 0;
    }
    void decIndex()
    {
        m_index --;
        if ( m_index < 0 )
            m_index = m_gallery.size() - 1;
    }
    string getExt( string path )
    {
        size_t i = path.rfind ( '.', path.size() );
        if ( i != string::npos ) 
        {
            return path.substr( i + 1, path.size() - i );
        }
        return string ( "" );
    }
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
    size_t size()
    {
        return m_gallery.size();
    }
private:
    int             m_index;
    vector<CImage*> m_gallery;
};
