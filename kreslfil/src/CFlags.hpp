#pragma once

using namespace std;

class CFlags
{
public:
    CFlags()
    {
        m_play        = false;
        m_stretch     = true;
        m_loadPallete = false;
        m_outputIndex = 0;
    }
    bool m_play;
    bool m_stretch;
    bool m_loadPallete;
    int  m_outputIndex;
};