#include "CFormatManager.hpp"
#include "CImage.hpp"

class CGallery
{
public:
    CGallery( vector<string> & paths )
    {
        CFormatManager manager;
        for (size_t i = 0; i < paths.size(); i++)
        {
            CFormat * format = manager.getFormat( paths[i] );
            CImage * image = new CImage( format->load( paths[i] ) );
            m_images.push_back( image );
        }
    }
    ~CGallery()
    {
        for (size_t i = 0; i < m_images.size(); i++)
            delete m_images[i];
    }

private:
    vector<CImage  *> m_images;
};