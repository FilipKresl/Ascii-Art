#include "CPixelMap.hpp"
#include "CFormat.hpp"

using namespace std;

class CFormatTGA : public CFormat
{
    vector<uint8_t> load ( const string & filename ) override
    {
        // ...
        // fstream f ( filename, ios::in | ios::binary );
        // if ( !f.is_open () ) 
        //     throw invalid_argument ( "File Not Found" );
        // f.seekg ( 0, ios::beg );
        // streampos beg = f.tellg();
        // f.seekg ( 0, ios::end );
        // streampos end = f.tellg();
        // int fileSize = end - beg;
        // f.seekg ( 0, ios::beg );
        // vector<uint8_t> buffer;
        // buffer.resize(fileSize);
        // f.read ( reinterpret_cast<char*> ( buffer.data() ), fileSize);
        // f.close();
        // int width  = buffer[12] + ( buffer[13] << 8 );
        // int height = buffer[14] + ( buffer[15] << 8 );
        // int index  = 18;
        // init( bdoStretch );
        vector<uint8_t> v;
        return v;
    }
    void fillPixelMap ( int width, int height, int index, CPixelMap & rpixMap ) override
    {

    }

};