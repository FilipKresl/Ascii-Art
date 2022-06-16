/**
 * @file COutputDebug.hpp
 * @brief file for derived COutput class COutputDebug
 */
#include "COutput.hpp"

#pragma once

/**
 * @brief derived class for printing in numbers
 */
class COutputDebug : public COutput
{
    /**
     * @brief initializes the pallete with pre-specified numbers
     */
    virtual void fillPallete()
    {
        m_palletes.clear();
        m_palletes.push_back( "01" );
        m_palletes.push_back( "10" );
        m_pal = 0;
    }
};