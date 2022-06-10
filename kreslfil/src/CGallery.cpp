#include "CGallery.hpp"
#include "CFlags.hpp"

CGallery::CGallery( vector<string> & paths, CFlags & rflags )
{
    CFormatManager manager;
    for (size_t i = 0; i < paths.size(); i++)
    {
        CFormat * format = manager.getFormat( paths[i] );
        CImage * image = new CImage( format->load( paths[i], rflags ) );
        m_images.push_back( image );
        // image->dumpPixels();
    }
}
CGallery::~CGallery()
{
    for (size_t i = 0; i < m_images.size(); i++)
        delete m_images[i];
}
