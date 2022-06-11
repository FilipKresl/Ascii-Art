#include "COutput.hpp"

class COutputSharp : public COutput
{
    virtual void fillPallete ()
    {
        m_palletes.clear();
        m_palletes.push_back( " -" );
        m_palletes.push_back( "- " );
        m_palletes.push_back( " ,-/" );
        m_palletes.push_back( "/-, " );
        m_palletes.push_back( "`-_/\\|I" );
        m_palletes.push_back( "I|\\/_-`" );
        m_pal = 0;
    }
};