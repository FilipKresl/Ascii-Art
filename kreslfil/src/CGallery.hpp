#include "CFormatManager.hpp"
#include "CImage.hpp"
#include "CFlags.hpp"

#pragma once

class CGallery
{
public:
    CGallery( vector<string> & paths, CFlags & rflags );
    ~CGallery();

private:
    vector<CImage  *> m_images;
};