/**
 * @file cmdline.hpp
 * @brief Header file for enabling receiving and processing input followed after "./file_name"
 */

#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

/**
 * @brief Parses command line:
 * -h for help,
 * -a for ascii file. 
 */
class CCommandLine 
{
public:
    typedef std::vector<std::string> vecStrings;

public:
    /**
     * @brief Creates a new CCommandLine object.
     * @param argc Number of arguments.
     * @param argv Array of arguments.
     */
    CCommandLine ( int argc, char ** argv )
    {
        m_argc = argc;
        m_argv = argv;
    }

    /**
     * @brief Parses the input followed after "./file_name" for further features. 
     * @return true If successful.
     * @return false If invalid arguments.
     */
    bool parse ()
    {
        // tbd
        if ( ( arg == "-h" ) || ( arg == "--help" ) ) 
            {
                showUsage(m_argv[0]);
                return false;
            }
        // tbd
        else if ( ( arg == "-a" ) || ( arg == "--ascii" ) ) 
        {
            if (i + 1 < m_argc)
            { 
                m_asciiFileName = m_argv [ ++ i ]; // Increment 'i' so we don't get the argument as the next argv[i].
            } 
            else // wrong arguments 
            { 
                std::cerr << "--ascii option requires one argument specifying a text file with ascii characters" << std::endl;
                return false;
            }  
        }
        // tbd
        return true;
    }

    // const std::string &  getAsciiFileName () const  { return m_asciiFileName; } 
    /**
     * @brief Get Image filenames from command line.
     * @return const vecStrings& vector of image filenames.
     */
    const vecStrings & getImageFileNames () const { return m_imageFileNames; }

private:
    /**
     * @brief Reads the content of ascii file specified by -a <ascii-file> in to m_asciiChar.
     */
    bool readAsciiFile ()
    {
        // tbd
    }

    /**
     * @brief Output when -help is called.
     */
    static void showUsage ( std::string name )
    {
        std::cerr << "USAGE: " << name << " [options] files...\n\n"
                << "OPTIONS:\n"
                << "\t-h,--help\t\tShow this help message\n"
                << "\t-a,--ascii <file>\tLoad text file with ASCII characters used to render the image\n\n"
                << "FILES: "
                << "\tone or more BMP or TGA files or wildcards; only images with 24 or 32 bits per pixel are supported\n"
                << std::endl;
    }

    std::string   m_ext;
    int           m_argc;
    char       ** m_argv;
    std::string   m_asciiFileName; 
    vecStrings    m_imageFileNames;
    std::string   m_asciiChars;
};