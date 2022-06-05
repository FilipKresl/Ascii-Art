/**
 * @file main.cpp
 * @brief Main entry point. 
 */

/*
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

#define D if(0)

using namespace std;

void ncursInit()
{
    initscr();
    cbreak();
    noecho();
}
void printHelp()
{
    ncursInit();
    printw ( "--HELP-- \n" );
    printw ( "commands: \n" );
    printw ( "  -h for help \n" );
    printw ( "  -p for play \n" );
    printw ( "  -l for inserting own pallete in a file (write the name of the file before the images) \n" );
    printw ( "  -n for natural look - initial stretching disabled \n" );
    printw ( "  -r for output in round Ascii (e.g. o80@) (default) \n" );
    printw ( "  -s for output in sharp Ascii (e.g. -/I#) \n\n" );
    // printw ( "  -c for output in color \n" );
    printw ( "examples: \n" );
    printw ( "  ./a.out img/johnny.bmp \n" );
    printw ( "  ./a.out img/albert.tga \n" );
    printw ( "  ./a.out -l palleteNumbers.txt img/cat2.bmp img/cat.bmp \n" );
    printw ( "  ./a.out -l palletePerfect.txt img/cat2.bmp img/cat.bmp \n" );
    printw ( "  ./a.out -s -p img/img*.bmp \n\n" );
    printw ( "editing: \n" );
    printw ( "  Z,X,C,V for different types of RESIZING \n" );
    printw ( "  N,M     for SWITCHING between images \n" );
    printw ( "  B       for RELOADING the image with initial setting \n" );
    printw ( "  K,L     for increasing/decreasing LIGHT for the current image \n" );
    printw ( "  W,A,S,D for MOVING the current image \n" );
    printw ( "  F       for DELETING the image \n" );
    printw ( "  G,H     for SWAPPING the image with previous/next one \n" );
    printw ( "  I       for INVERTING the colors \n" );
    printw ( "  O,P     for changing the PALLETE \n" );
    printw ( "  U       for PLAY/STOP \n" );
    printw ( "  Y       for changing the Direction of playing \n" );
    
    refresh();
}
void printError()
{        
    ncursInit();
    printw( "--WRONG INPUT--\n" );
    printw( "type:\n" );
    printw( "   ./a.out -h\n" );
    printw( "for help\n" );
    refresh();
}
bool processCommands (  vector<char> & commands, bool & rbPlaying, 
                        int & routIndex, bool & rloadPallete, bool & rbdoStretch)
{
    for (size_t i = 0; i < commands.size(); i++)
    {
        char c = commands[i];
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
string getExt( string path )
    {
        size_t i = path.rfind ( '.', path.size() );
        if ( i != string::npos ) 
        {
            return path.substr( i + 1, path.size() - i );
        }
        return string ( "" );
    }
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

int main ( int argc, char** argv )
{   
    CCommandLine cmd ( argc, argv );
    vector<string> paths  = cmd.handoverImgs();
    vector<char> commands = cmd.handoverCmds();

    bool bContinue  = true;
    bool bDirection = true;
    bool bPlaying   = false;
    bool bdoStretch = true;
    bool bPlayAllowed   = true;
    bool bisNewPallete  = false;
    int  outIndex       = 0;
    string pallete      = "";
    
    if ( cmd.getError() == true )
    {
        printError();
        return 0;
    }
    if ( processCommands( commands, bPlaying, outIndex, bisNewPallete, bdoStretch ) == false )
    {
        printHelp();
        return 0;
    }
    if ( bisNewPallete == true )
    {
        pallete = loadPallete ( paths );
        if ( pallete == "" )
        {
            printError();
            return 0;
        }
    }
    CGallery gal;
    try
    {
        gal.init ( paths, bdoStretch );
    }
    catch ( ... )
    {
        printError();
        return 0;
    }
    
    if ( gal.size() == 0 )
    {
        printError();
        return 0;
    }
    if ( gal.size() <= 1 )
    {
        bPlayAllowed = false;
        bPlaying     = false;
    }

    vector<COutput*> outVec;
    outVec.push_back ( new COutputRound );
    outVec.push_back ( new COutputSharp );
    COutput * pOutput = outVec[outIndex];
    if ( bisNewPallete == false )
        pOutput->fillPallete();
    else
        pOutput->setPallete( pallete );

    pOutput->readImg ( gal.getImage() );
    pOutput->printArt();
    while ( bContinue )
    {
        if ( bPlaying ) // play automatically
        {
            nodelay(stdscr, TRUE);
            if ( bDirection )
                gal.incIndex();
            else 
                gal.decIndex();

            pOutput->readImg ( gal.getImage() );
            pOutput->printArt();
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        else            // stops playing
            nodelay(stdscr, FALSE);

        char c = tolower ( getch() );
        switch ( c )
        {
        // change the Ascii pallete
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
        
        // move the image
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
            
        // fit the image in the screen
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

        // order/delete the images
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

        // play / stop
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

    for (size_t i = 0; i < outVec.size(); i++)
    {
        delete outVec[i];
    }
    
    return 0;
}
