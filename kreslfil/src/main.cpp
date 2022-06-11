#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <assert.h>
#include <ncurses.h>
#include <thread>
#include <chrono>

#include "CGallery.hpp"
#include "CCommandLine.hpp"
#include "CFlags.hpp"
#include "CMessages.hpp"
#include "COutput.hpp"
#include "COutputRound.hpp"
#include "COutputSharp.hpp"
#include "CEffectManager.hpp"

using namespace std;

int main ( int argc, char ** argv )
{
    CMessages mes;
    CCommandLine cmd( argc, argv );
    CFlags flags;
    if ( ! cmd.processCommands( flags ) )
    {
        mes.printHelp();
        return 0;
    }
        
    vector<string> paths = cmd.handoverImgs();
    try
    {
        CGallery gal( paths, flags );
        cout << "check 1" << endl;
        COutput * pout;
        if    ( flags.m_outputIndex == 0 )
            pout = new COutputRound();
        else
            pout = new COutputSharp();
        cout << "check 2" << endl;
        pout->fillPallete();
        CEffectManager efMan;
        pout->readImg( gal.getImage() );
        pout->printArt();
        while ( flags.m_continue )
        {
            char c = tolower( getch() );
            efMan.processEffect( c, pout, flags, gal );

            if ( flags.m_play )
                this_thread::sleep_for(chrono::milliseconds(100));
        }
        delete pout;
    }
    catch( ... )
    {
        cout << "excep" << endl;
        mes.printError();
        return 0;
    }

    endwin();

    return 0;
}
