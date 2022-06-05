#include <iostream>
#include <string>
#include <vector>

#pragma once

using namespace std;

class CCommandLine
{
public:
    CCommandLine ( int argc, char** argv )
    {
        m_error = false;
        m_argc = argc;
        m_argv = argv;
        parse();
        // dumpLine();
    }
    void parse ()
    {
        for (int i = 1; i < m_argc; i++)
        {
            if ( m_argv[i][0] == '-' )
                readCommand( i );
            else
                readImage( i );
        }
    }
    void readImage ( int i )
    {
        string s;
        s = m_argv[i];
        m_imgs.push_back( s );
    }
    void readCommand ( int i )
    {
        m_commands.push_back( m_argv[i][1] );
        if ( m_argv[i][1] == '\0' || m_argv[i][2] != '\0' )
            m_error = true;
    }
    vector<string> handoverImgs ()
    {
        return m_imgs;
    }
    vector<char> handoverCmds ()
    {
        return m_commands;
    }
    void dumpLine ()
    {
        for (int i = 1; i < m_argc; i++)
        {
            cout << m_argv[i] << endl;
        }
    }
    void dumpIaC ()
    {
        for (int i = 0; i < m_imgs.size(); i++)
        {
            cout << m_imgs[i] << endl;;
        }
        for (int i = 0; i < m_commands.size(); i++)
        {
            cout << m_commands[i] << endl;;
        }
    }
    bool getError ()
    {
        return m_error;
    }

private:
    int             m_argc; 
    char         ** m_argv;
    vector<string>  m_imgs;
    vector<char>    m_commands;
    bool            m_error;
};
