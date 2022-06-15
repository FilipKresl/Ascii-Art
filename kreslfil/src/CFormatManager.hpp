/**
 * @file CFormatManager.hpp
 * @brief file for class CFormatManager, manages derived CFormat classes
 */
#include <map>

#include "CFormatBMP.hpp"
#include "CFormatTGA.hpp"

#pragma once

using namespace std;

/**
 * @brief class for choosing the right CFormat derived class based on image's extension
 */
class CFormatManager
{
public:
    /**
     * @brief construct a new CFormatManager object
     */
    CFormatManager();
    /**
     * @brief destroy the CFormatManager object
     */
    ~CFormatManager();
    /**
     * @brief decides which CFormat derived class should be returned
     * @param filename path to the image
     * @return CFormat* pointer to CFormat derived class
     */
    CFormat * getFormat ( const string & filename ) const;
private:
    const string getExt ( const string & filename ) const;
    map<string, CFormat *> m_formats;
};
