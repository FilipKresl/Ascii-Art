#include <string>
#include <map>

#include "CFormatManager.hpp"

using namespace std;
    CFormatManager::CFormatManager()
    {
        m_formats.insert({ "bmp", new CFormatBMP() });
        m_formats.insert({ "tga", new CFormatTGA() });
    }
    CFormatManager::~CFormatManager()
    {
        map<string, CFormat *>::iterator it;
        for (it = m_formats.begin(); it != m_formats.end(); it++)
        {
            delete it->second;
        }
    }
    // const CFormat * getFormat ( const string & filename ) const
    CFormat * CFormatManager::getFormat ( const string & filename ) const
    {
        string extension = getExt( filename );
        if ( m_formats.count( extension ) == 0 )
            throw nullptr;
        return m_formats.at( extension );
    }
    const string CFormatManager::getExt ( const string & filename ) const
    {
        size_t i = filename.rfind ( '.', filename.size() );
        if ( i != string::npos ) 
        {
            return filename.substr( i + 1, filename.size() - i );
        }
        return string ( "" );
    }
