#include <vector>

#include "rgba.hpp"
#include "CPixelMap.hpp"
#include "CFlags.hpp"
#include "CFormat.hpp"

using namespace std;

void CFormat::stretch( CPixelMap & rpixMap ) const
{
    int width = rpixMap.getWidth();
    int height = rpixMap.getHeight();

    vector<uint8_t> tmp;
    vector<uint8_t> & grayPixels = rpixMap.getGrayPixelsRef();
    for (int h = 0; h < height-1; h+=2)
    {
        for (int w = 0; w < width; w++)
            tmp.push_back( (grayPixels[h*width + w] + grayPixels[(h+1)*width + w]) / 2 );
    }
    height /= 2;
    rpixMap.setHeight( height );
    rpixMap.setGrayPixels( tmp );
}