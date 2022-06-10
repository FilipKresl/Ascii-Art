#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "CFlags.hpp"

#pragma once

using namespace std;
class CCommandLine
{
public:
    CCommandLine ( int argc, char** argv );
    bool processCommands ( CFlags & rflags );
    string loadPallete( vector<string> & rpaths );
    vector<string> handoverImgs();
    void dumpLine();
    void dumpIaC();
    bool getError();
    
private:
    void parse();
    string getExt( string path );
    void storeFile ( int i );
    void storeCommand ( int i );

private:
    int             m_argc; 
    char         ** m_argv;
    vector<string>  m_imgs;
    vector<char>    m_commands;
    bool            m_error;
};
