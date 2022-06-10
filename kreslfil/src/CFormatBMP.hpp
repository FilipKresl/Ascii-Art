#include "CPixelMap.hpp"
#include "CFormat.hpp"

using namespace std;

class CFormatBMP : public CFormat
{
public:
    vector<uint8_t> load ( const string & filename ) override;
    
    void fillPixelMap ( int width, int height, int index, CPixelMap & rpixMap ) override;
};
