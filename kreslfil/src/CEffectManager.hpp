#include "COutput.hpp"
#include "CFlags.hpp"
#include "CGallery.hpp"

#pragma once

using namespace std;

class CEffectManager
{
public:
    void processEffect( char c, COutput * pout, CFlags & rflags, CGallery & rgal );

private:
    void play( COutput * pout, CGallery & rgal, CFlags & rflags );
};