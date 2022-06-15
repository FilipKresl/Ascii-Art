#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "CFlags.hpp"
#include "CCommandLine.hpp"

using namespace std;

CCommandLine::CCommandLine ( int argc, char** argv )
{
    m_error = false;
    m_argc = argc;
    m_argv = argv;
    parse();
}
bool CCommandLine::processCommands ( CFlags & rflags )
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
            rflags.m_play = true;
            break;
        case 'l':
            rflags.m_loadPallete = true;
            break;
        case 'n':
            rflags.m_stretch = false;
            break;
        case 'r':
            rflags.m_outputIndex = 0;
            break;
        case 's':
            rflags.m_outputIndex = 1;
            break;
        default:
            return false;
            break;
        }
    }
    return true;
}
string CCommandLine::loadPallete( vector<string> & rpaths )
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
vector<string> CCommandLine::handoverImgs()
{
    return m_imgs;
}
void CCommandLine::dumpLine()
{
    for (int i = 1; i < m_argc; i++)
        cout << m_argv[i] << endl;
}
void CCommandLine::dumpIaC()
{
    for (size_t i = 0; i < m_imgs.size(); i++)
        cout << m_imgs[i] << endl;;
    for (size_t i = 0; i < m_commands.size(); i++)
        cout << m_commands[i] << endl;;
}
bool CCommandLine::getError()
{
    return m_error;
}
void CCommandLine::parse()
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
string CCommandLine::getExt( string path )
{
    size_t i = path.rfind ( '.', path.size() );
    if ( i != string::npos ) 
    {
        return path.substr( i + 1, path.size() - i );
    }
    return string ( "" );
}
void CCommandLine::storeFile ( int i )
{
    string s;
    s = m_argv[i];
    m_imgs.push_back( s );
}
void CCommandLine::storeCommand ( int i )
{
    m_commands.push_back( m_argv[i][1] );
    if ( m_argv[i][1] == '\0' || m_argv[i][2] != '\0' )
        m_error = true;
}
