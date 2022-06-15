/**
 * @file COutputRound.hpp
 * @brief file for derived COutput class COutputRound.hpp
 */
#include "COutput.hpp"

/**
 * @brief derived class for printing in round-shaped chars
 */
class COutputRound : public COutput
{
    /**
     * @brief initializes the pallete with pre-specified round-shaoed chars
     */
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