/**
 * @file CEffectManager.hpp
 * @brief file for class CEffectManager, manages which effect should be called
 */
#include "COutput.hpp"
#include "CFlags.hpp"
#include "CGallery.hpp"

#pragma once

using namespace std;

/**
 * @brief manages which effect should be called
 */
class CEffectManager
{
public:
    /**
     * @brief calls effect methods based on input char 'c'
     * 
     * @param c char that was pressed
     * @param pout pointer to derived COutput instance
     * @param rflags reference to a class containing flags
     * @param rgal reference to a CGallery instance
     */
    void processEffect( char c, COutput * pout, CFlags & rflags, CGallery & rgal );

private:
    void play( COutput * pout, CGallery & rgal, CFlags & rflags );
};