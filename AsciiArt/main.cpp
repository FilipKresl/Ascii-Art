/**
 * @file main.cpp
 * @author Filip Kresl (kreslfil)
 * @brief main entry point
 * @version 1.0
 * @date 2022-06-05
 */

/* compiler
clear; g++ -Wall -pedantic main.cpp -lncurses
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <assert.h>
#include <ncurses.h>
#include <thread>
#include <chrono>

#include "CCommandLine.hpp"
#include "CImage.hpp"
#include "CGallery.hpp"
#include "COutput.hpp"

using namespace std;

int main ( int argc, char** argv )
{   
    CCommandLine cmd ( argc, argv );
    vector<string> paths  = cmd.handoverImgs();

    bool bContinue  = true;
    bool bDirection = true;
    bool bPlaying   = false;
    bool bdoStretch = true;
    bool bPlayAllowed   = true;
    bool bisNewPallete  = false;
    int  outIndex       = 0;
    string pallete      = "";
    CMessages mes;
    
    // if wrong format for a command
    if ( cmd.getError() == true )
    {
        mes.printError();
        return 0;
    }
    // sets flags from commands
    // returns false if user asks for help manual
    if ( cmd.processCommands( bPlaying, outIndex, bisNewPallete, bdoStretch ) == false )
    {
        mes.printHelp();
        return 0;
    }
    // if user wants to load his own Ascii-Pallete
    if ( bisNewPallete == true )
    {
        pallete = cmd.loadPallete ( paths );
        // if Pallete not found or in wrong format
        if ( pallete == "" )
        {
            mes.printError();
            return 0;
        }
    }
    CGallery gal;
    try
    { 
        // throws an exception if image name was not found
        gal.init ( paths, bdoStretch );
    }
    catch ( ... )
    {
        mes.printError();
        return 0;
    }
    // if not valid image could have been loaded
    if ( gal.size() == 0 )
    {
        mes.printError();
        return 0;
    }
    // if only 1 image, don't allow automatic switching between images
    if ( gal.size() <= 1 )
    {
        bPlayAllowed = false;
        bPlaying     = false;
    }
    // output vector - stores derivated output-classes via pointers, enables polymorphism
    vector<COutput*> outVec;
    outVec.push_back ( new COutputRound );
    outVec.push_back ( new COutputSharp );
    COutput * pOutput = outVec[outIndex];
    // if default or users pallete should be used
    if ( bisNewPallete == false )
        pOutput->fillPallete();
    else
        pOutput->setPallete( pallete );

    pOutput->readImg ( gal.getImage() );
    pOutput->printArt();
    while ( bContinue )
    {
        // repeatedly switches to next image, waits for 0.1 sec
        if ( bPlaying )
        {
            nodelay(stdscr, TRUE);
            // if next or previous image should be loaded
            if ( bDirection )
                gal.incIndex();
            else 
                gal.decIndex();

            pOutput->readImg ( gal.getImage() );
            pOutput->printArt();
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        // stops playing
        else 
            nodelay(stdscr, FALSE);

        // main switch - reads a char if pressed and decides which edit function should be called
        char c = tolower ( getch() );
        switch ( c )
        {
        // change the Ascii-Pallete
        case 'i':
            pOutput->invertPallete();
            pOutput->printArt();
            break;
        case 'p':
            pOutput->biggerPallete();
            pOutput->printArt();
            break;
        case 'o':
            pOutput->smallerPallete();
            pOutput->printArt();
            break;

        // read same/previous/next image
        case 'b':
            pOutput->setResizeMod( 0 );
            pOutput->readImg ( gal.getImage() );
            pOutput->printArt();
            break;
        case 'm':
            gal.incIndex();
            pOutput->readImg ( gal.getImage() );
            pOutput->printArt();
            break;
        case 'n':
            gal.decIndex();
            pOutput->readImg ( gal.getImage() );
            pOutput->printArt();
            break;
        
        // move with the image
        case 'w':
            pOutput->moveUp();
            pOutput->printArt();
            break;
        case 's':
            pOutput->moveDown();
            pOutput->printArt();
            break;
        case 'd':
            pOutput->moveRight();
            pOutput->printArt();
            break;
        case 'a':
            pOutput->moveLeft();
            pOutput->printArt();
            break;
            
        // resize the image
        case 'z':
            pOutput->setResizeMod( 1 );
            pOutput->printArt();
            break;
        case 'x':
            pOutput->setResizeMod( 2 );
            pOutput->printArt();
            break;
        case 'c':
            pOutput->setResizeMod( 3 );
            pOutput->printArt();
            break;
        case 'v':
            pOutput->setResizeMod( 4 );
            pOutput->printArt();
            break;

        // brighten/darken the image
        case 'l':
            pOutput->lightUp();
            pOutput->printArt();
            break;
        case 'k':
            pOutput->lightDown();
            pOutput->printArt();
            break;

        // change the order of images or delete one
        case 'f':
            gal.deleteImg();
            pOutput->readImg( gal.getImage() );
            pOutput->printArt();
            break;
        case 'g':
            gal.moveImgBack();
            pOutput->readImg( gal.getImage() );
            pOutput->printArt();
            break;
        case 'h':
            gal.moveImgForward();
            pOutput->readImg( gal.getImage() );
            pOutput->printArt();
            break;

        // play & stop
        case 'u':
            if ( bPlayAllowed )
                bPlaying = ! bPlaying;
            break;
        case 'y':
            bDirection = !bDirection;
            break;
        
        // quit
        case 'q':
            bContinue = false;
            break;

        default:
            pOutput->checkShifts();
            pOutput->printArt();
            break;
        }
    } 

    endwin();

    // "destructor" for allocated Output-Classes
    for (size_t i = 0; i < outVec.size(); i++)
    {
        delete outVec[i];
    }
    
    return 0;
}
