#include "CFormatBMP.hpp"
#include "CFormatTGA.hpp"

using namespace std;

class CFormatManager
{
public:
    CFormatManager();
    ~CFormatManager();

    // const CFormat * getFormat ( const string & filename ) const
    CFormat * getFormat ( const string & filename ) const;
private:
    const string getExt ( const string & filename ) const;
    map<string, CFormat *> m_formats;
};
