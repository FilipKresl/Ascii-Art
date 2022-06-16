/**
 * @file CCommandLine.hpp
 * @brief file for class CCommandLine, processes everything given during lauch by the user 
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "CFlags.hpp"

#pragma once

using namespace std;
/**
 * @brief processes everything given by the user when launched
 */
class CCommandLine
{
public:
    /**
     * @brief Constructs a new CCommandLine object
     * 
     * @param argc number of arguments given by user
     * @param argv arguments given by user
     */
    CCommandLine ( int argc, char** argv );
    /**
     * @brief set propre flags for parsed commands
     * 
     * @param rflags reference to a class containing flags
     * @return true -> continue
     * @return false -> -h has been loaded
     */
    bool processCommands ( CFlags & rflags ) const;
     /**
     * @brief loads user's pallete from a file
     * 
     * @param rpaths vector containing path to every given file
     * @return pallete as a string 
     */
    string loadPallete( vector<string> & rpaths );
    /**
     * @brief getter for a member vector containing paths to all given files
     * 
     * @return vector<string> filled with paths to every given file
     */
    vector<string> handoverImgs() const;
    /**
     * @brief debug dump of all argumentes 
     */
    void dumpLine() const;
    /**
     * @brief debug dump of all file_names and commands
     */
    void dumpIaC() const;
    /**
     * @brief getter if a error has been detected
     */
    bool getError() const;
    
private:
    /**
     * @brief reads all arguments and stores them to vector of either commands or files
     */
    void parse();
    /**
     * @brief reads the postfix (extension) of a file
     * 
     * @param path path to a file
     * @return extension as a string 
     */
    string getExt( const string path );
    /**
     * @brief stores file to a member vector for later use
     */
    void storeFile ( const int i );
    /**
     * @brief stores command to a member vector for later use
     */
    void storeCommand ( const int i );

private:
    int             m_argc; 
    char         ** m_argv;
    vector<string>  m_imgs;
    vector<char>    m_commands;
    bool            m_error;
};
