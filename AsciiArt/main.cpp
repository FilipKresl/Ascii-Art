/**
 * @file main.cpp
 * @brief Main entry point. 
 */

// clear; g++ -Wall -pedantic main.cpp && ./a.out
// clear; g++ -Wall -pedantic main.cpp -lncurses && ./a.out johnny.bmp
// clear; g++ -Wall -pedantic main.cpp -lncurses && ./a.out img0.bmp img1.bmp img2.bmp img3.bmp img4.bmp img5.bmp img6.bmp img7.bmp

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <assert.h>
#include <ncurses.h>

#include "CCommandLine.hpp"
#include "CImage.hpp"
#include "CGallery.hpp"
#include "COutput.hpp"

#define D if(0)

using namespace std;

int main ( int argc, char** argv )
{   
    vector<COutput*> pOutVec;
    pOutVec.push_back ( new COutput          );
    pOutVec.push_back ( new CHexaOutput      );
    pOutVec.push_back ( new CColorOutput     );
    pOutVec.push_back ( new CFewAsciiOutput  );
    pOutVec.push_back ( new CManyAsciiOutput );
    int outIndex = 0;

    CCommandLine cmd ( argc, argv );
    vector<string> paths = cmd.handoverImgs();
    CGallery gal ( paths );

    pOutVec[ outIndex ]->readImg ( gal.getImage() );

    bool bContinue = true;
    while ( bContinue )
    {
        char c = tolower ( getch() );
        switch ( c )
        {

        // change the Ascii pallete
        case 'i':
            pOutVec[ outIndex ]->invertPallete();
            break;
        case 'p':
            pOutVec[ outIndex ]->biggerPallete();
            break;
        case 'o':
            pOutVec[ outIndex ]->smallerPallete();
            break;

        // read same/previous/next image
        case 'b':
            pOutVec[ outIndex ]->readImg ( gal.getImage() );
            break;
        case 'm':
            gal.incIndex();
            pOutVec[ outIndex ]->readImg ( gal.getImage() );
            break;
        case 'n':
            gal.decIndex();
            pOutVec[ outIndex ]->readImg ( gal.getImage() );
            break;
        
        // move the image
        case 'w':
            pOutVec[ outIndex ]->moveUp();
            break;
        case 's':
            pOutVec[ outIndex ]->moveDown();
            break;
        case 'd':
            pOutVec[ outIndex ]->moveRight();
            break;
        case 'a':
            pOutVec[ outIndex ]->moveLeft();
            break;
            
        // fit the image in the screen
        case 'z':
            pOutVec[ outIndex ]->fitByHeight();
            break;
        case 'x':
            pOutVec[ outIndex ]->fitByWidth();
            break;
        case 'c':
            pOutVec[ outIndex ]->fitPerfect();
            break;
        case 'v':
            pOutVec[ outIndex ]->fitStretch();
            break;

        // brighten/darken the image
        case 'l':
            pOutVec[ outIndex ]->lightUp();
            break;
        case 'k':
            pOutVec[ outIndex ]->lightDown();
            break;

        // order/delete the images
        case 'f':
            gal.deleteImg();
            pOutVec[ outIndex ]->readImg( gal.getImage() );
            break;
        case 'g':
            gal.moveImgBack();
            pOutVec[ outIndex ]->readImg( gal.getImage() );
            break;
        case 'h':
            gal.moveImgForward();
            pOutVec[ outIndex ]->readImg( gal.getImage() );
            break;

        // quit
        case 'q':
            bContinue = false;
            break;

        default:
            pOutVec[ outIndex ]->checkShifts();
            break;
        }
    } 

    endwin();

    return 0;
}
