/**
 * @file CCommandLine.hpp
 * @brief CCommandLine
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#pragma once

using namespace std;
/**
 * @brief Class for reading input from command line and processing commands 
 */
class CCommandLine
{
public:
    /**
     * @brief Construct a new CCommandLine object
     * @param argc counter of arguments
     * @param argv pointer to separate arguments (e.g. commands, names of images, ...)
     */
    CCommandLine ( int argc, char** argv )
    {
        m_error = false;
        m_argc = argc;
        m_argv = argv;
        parse();
    }
    /**
     * @brief reads all commands and decides which flag to set
     * 
     * @param rbPlaying if automatic play should be enabled right after launch
     * @param routIndex reference output index - which Output-Class should be selected
     * @param rloadPallete if user's pallete should be loaded
     * @param rbdoStretch if user wants to keep images unstreched
     * @return true if continue to process images
     * @return false if to print help and terminate
     */
    bool processCommands ( bool & rbPlaying,    int  & routIndex, 
                           bool & rloadPallete, bool & rbdoStretch )
    {
        for (size_t i = 0; i < m_commands.size(); i++)
        {
            char c = m_commands[i];
            switch ( c )
            {
            case 'h':
                return false;
                break;
            case 'p':
                rbPlaying = true;
                break;
            case 'l':
                rloadPallete = true;
                break;
            case 'n':
                rbdoStretch = false;
                break;
            case 'r':
                routIndex = 0;
                break;
            case 's':
                routIndex = 1;
                break;
            default:
                break;
            }
        }
        return true;
    }
    /**
     * @brief loads user's pallete from a file
     * 
     * @param rpaths vector containing paths to each file
     * @return pallete as a string 
     */
    string loadPallete( vector<string> & rpaths )
    {
        if ( rpaths.size() == 0 || getExt( rpaths[0]) != "txt" )
            return "";
        string pathPallete = rpaths[0];
        rpaths.erase( rpaths.begin() );
        string pallete;
        ifstream f ( pathPallete );
        if ( !f.is_open () ) 
            return "";
        while ( getline ( f, pallete ) ) {}
        f.close();
        return pallete;
    }
    /**
     * @brief getter for a member vector containing all images
     * 
     * @return vector<string> m_imgs
     */
    vector<string> handoverImgs()
    {
        return m_imgs;
    }
    /**
     * @brief debug dump of all argumentes 
     */
    void dumpLine()
    {
        for (int i = 1; i < m_argc; i++)
        {
            cout << m_argv[i] << endl;
        }
    }
    /**
     * @brief debug dump of all file names and commands
     */
    void dumpIaC()
    {
        for (size_t i = 0; i < m_imgs.size(); i++)
        {
            cout << m_imgs[i] << endl;;
        }
        for (size_t i = 0; i < m_commands.size(); i++)
        {
            cout << m_commands[i] << endl;;
        }
    }
    /**
     * @brief getter if a error has been detected
     */
    bool getError()
    {
        return m_error;
    }
private:
    /**
     * @brief reads all arguments and stores them to either commands or files
     */
    void parse()
    {
        for (int i = 1; i < m_argc; i++)
        {
            // all commands have '-' as prefix
            if ( m_argv[i][0] == '-' )
                storeCommand( i );
            else
                storeFile( i );
        }
    }
    /**
     * @brief reads the postfix (extension) of a file
     * 
     * @param path path to a file
     * @return extension as a string 
     */
    string getExt( string path )
    {
        size_t i = path.rfind ( '.', path.size() );
        if ( i != string::npos ) 
        {
            return path.substr( i + 1, path.size() - i );
        }
        return string ( "" );
    }
    /**
     * @brief stores file to a member vector for later use
     */
    void storeFile ( int i )
    {
        string s;
        s = m_argv[i];
        m_imgs.push_back( s );
    }
    /**
     * @brief stores command to a member vector for later use
     */
    void storeCommand ( int i )
    {
        m_commands.push_back( m_argv[i][1] );
        if ( m_argv[i][1] == '\0' || m_argv[i][2] != '\0' )
            m_error = true;
    }

private:
    int             m_argc; 
    char         ** m_argv;
    vector<string>  m_imgs;
    vector<char>    m_commands;
    bool            m_error;
};
