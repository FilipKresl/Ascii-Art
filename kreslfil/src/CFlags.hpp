/**
 * @file CFlags.hpp
 * @brief file for class CFlags, contains boolean member variables called flags
 */

#pragma once

using namespace std;

/**
 * @brief class for storing values of flags
 */
class CFlags
{
public:
    /**
     * @brief Construct a new CFlags object and initializes the values of flags
     */
    CFlags()
    {
        m_play        = false;
        m_stretch     = true;
        m_continue    = true;
        m_direction   = true;
        m_playAllowed = true;
        m_loadPallete = false;
        m_outputIndex = 0;
    }
    bool m_play;        ///< true->play
    bool m_stretch;     ///< true->stretch images during initialization
    bool m_continue;    ///< true->continue in the main while()
    bool m_direction;   ///< true->from L to R
    bool m_playAllowed; ///< true->there are more than 2 images
    bool m_loadPallete; ///< true->read pallete given by user
    int  m_outputIndex; ///< which COutput derived class is active
};