/**
 * @file main.cpp
 * @author Filip 'kreslfil' Kresl
 * @brief main entry point
 * @version 2.0
 * @date 2022-06-16
 */
/*! @mainpage Ascii-Art
 *
 * @section Introduction
 *
 * This c++ program enables to load images from a file and convert them into Ascii chars. \n
 * User is then allowed to modify the output while program is running
 *
 * @section Unpopular_opinion Unpopular Opinion
 * 
 * Although, some may argue Ascii-Art is not pretty. It actually is.
 * 
 * @section Commands Help: Commands
 * 
 *  -h for help \n
 *  -p for play \n
 *  -l for inserting own pallete in a file (write the name of the file before the images) \n
 *  -n for natural look - initial stretching disabled \n
 *  -r for output in round Ascii (e.g. o80@) (default) \n
 *  -s for output in sharp Ascii (e.g. -/I#) \n
 *
 * @section Editing Help: Editing 
 * 
 * Z,X,C,V for different types of RESIZING \n
 * N,M     for SWITCHING between images \n
 * B       for RELOADING the image with initial setting \n
 * K,L     for increasing/decreasing LIGHT for the current image \n
 * W,A,S,D for MOVING the current image \n
 * F       for DELETING the image \n
 * G,H     for SWAPPING the image with previous/next one \n
 * I       for INVERTING the colors \n
 * O,P     for changing the PALLETE \n
 * U       for PLAY/STOP \n
 * Y       for changing the DIRECTION of playing \n
 */

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

/**
 * @brief MAIN
 * 
 * @param argc number of arguments given by user
 * @param argv arguments given by user
 */
int main ( int argc, char ** argv )
{
    CMessages mes;
    if ( argc < 2 )
    {
        mes.printError();
        return 0;
    }
    CCommandLine cmd( argc, argv );

    CFlags flags;
    if ( cmd.getError() || ! cmd.processCommands( flags ) )
    {
        mes.printHelp();
        return 0;
    }
    vector<string> paths = cmd.handoverImgs();
    string pallete = "";
    if ( flags.m_loadPallete )
    {
        pallete = cmd.loadPallete( paths );
        // if Pallete not found or in wrong format
        if ( pallete == "" )
        {
            mes.printError();
            return 0;
        }
    }
    // if no images given
    if ( paths.size() == 0 )
    {
        mes.printError();
        return 0;
    }
    try
    {
        CGallery gal( paths, flags );
        COutput * pout;

        if ( flags.m_outputIndex == 0 )
            pout = new COutputRound();
        else
            pout = new COutputSharp();

        if ( pallete != "" )
            pout->setPallete( pallete );
        else 
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
        mes.printError();
        return 0;
    }

    endwin();

    return 0;
}
