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

using namespace std;

int main ( int argc, char ** argv )
{
    cout << "main {" << endl;
    CCommandLine cmd( argc, argv );
    CFlags flags;
    cmd.processCommands( flags );
    vector<string> paths = cmd.handoverImgs();
    try
    {
        CGallery gal( paths, flags );
    }
    catch( ... )
    {
       cout << "failed" << endl;
    }

    cout << "} main" << endl;
    return 0;
}
