#include "CGallery.hpp"
#include "CFlags.hpp"

CGallery::CGallery( vector<string> & paths, CFlags & rflags )
{
    m_index = 0;
    CFormatManager manager;
    for (size_t i = 0; i < paths.size(); i++)
    {
        CFormat * format = manager.getFormat( paths[i] );
        CImage * image = new CImage( format->load( paths[i], rflags ) );
        m_images.push_back( image );
    }
}
CGallery::~CGallery()
{
    for (size_t i = 0; i < m_images.size(); i++)
        delete m_images[i];
}
void CGallery::incIndex()
{
    m_index ++;
    if ( m_index >= m_images.size() )
        m_index = 0;
}
void CGallery::decIndex()
{
    m_index --;
    if ( m_index < 0 || m_index >= m_images.size() )
        m_index = m_images.size() - 1;
}
void CGallery::deleteImg()
{
    vector<CImage*>::iterator it;
    it = m_images.begin();
    it += m_index;
    CImage * p = m_images[m_index];
    if ( m_images.size() > 1 )
    {
        m_images.erase( it );
        if ( m_index >= m_images.size() )
            m_index = 0;
        delete p;
    }
}
void CGallery::moveImgForward()
{
    if ( m_images.size() > 1 )
    {
        size_t indexNext = m_index + 1;
        if ( indexNext >= m_images.size() )
            indexNext = 0;
        CImage * p = m_images[ m_index ];
        m_images[ m_index ] = m_images[ indexNext ];
        m_images[ indexNext ] = p;
    }
}
void CGallery::moveImgBack()
{
    if ( m_images.size() > 1 )
    {
        size_t indexPrev = m_index - 1;
        if ( indexPrev < 0 )
            indexPrev = m_images.size() - 1;
        CImage * p = m_images[ m_index ];
        m_images[ m_index ] = m_images[ indexPrev ];
        m_images[ indexPrev ] = p;
    }
}
CImage * CGallery::getImage()
{
    return m_images[m_index];
}
