/**
 * @file COutputSharp.hpp
 * @brief file for derived COutput class COutputSharp.hpp
 */
#include "COutput.hpp"

/**
 * @brief derived class for printing in sharp-shaped chars
 */
class COutputSharp : public COutput
{
    /**
     * @brief initializes the pallete with pre-specified sharp-shaoed chars
     */
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