#include "CFormatManager.hpp"
#include "CImage.hpp"
#include "CFlags.hpp"

#pragma once

class CGallery
{
public:
    CGallery( vector<string> & paths, CFlags & rflags );
    ~CGallery();
    void incIndex();
    void decIndex();
    void deleteImg();
    void moveImgForward();
    void moveImgBack();
    CImage * getImage();
private:
    size_t m_index;
    vector<CImage  *> m_images;
};