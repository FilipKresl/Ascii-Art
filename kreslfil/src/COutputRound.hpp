#include "COutput.hpp"

class COutputRound : public COutput
{
    virtual void fillPallete()
    {
        m_palletes.clear();
        m_palletes.push_back( " o" );
        m_palletes.push_back( "o " );
        m_palletes.push_back( " .oO80" );
        m_palletes.push_back( "08Oo. " );
        m_pal = 0;
    }
};