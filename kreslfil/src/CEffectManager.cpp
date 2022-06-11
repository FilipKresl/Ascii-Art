#include <chrono>

#include "CEffectManager.hpp"
#include "COutput.hpp"
#include "CFlags.hpp"
#include "CGallery.hpp"

using namespace std;

void CEffectManager::processEffect( char c, COutput * pout, CFlags & rflags, CGallery & rgal )
{
    switch ( c )
    {
    // change the Ascii-Pallete
    case 'i':
        pout->invertPallete();
        break;
    case 'p':
        pout->biggerPallete();
        break;
    case 'o':
        pout->smallerPallete();
        break;

    // read same/previous/next image
    case 'b':
        pout->setResizeMod( 0 );
        pout->readImg ( rgal.getImage() );
        break;
    case 'm':
        rgal.incIndex();
        pout->readImg ( rgal.getImage() );
        break;
    case 'n':
        rgal.decIndex();
        pout->readImg ( rgal.getImage() );
        break;
    
    // move with the image
    case 'w':
        pout->moveUp();
        break;
    case 's':
        pout->moveDown();
        break;
    case 'd':
        pout->moveRight();
        break;
    case 'a':
        pout->moveLeft();
        break;
        
    // resize the image
    case 'z':
        pout->setResizeMod( 1 );
        break;
    case 'x':
        pout->setResizeMod( 2 );
        break;
    case 'c':
        pout->setResizeMod( 3 );
        break;
    case 'v':
        pout->setResizeMod( 4 );
        break;

    // brighten/darken the image
    case 'l':
        pout->lightUp();
        break;
    case 'k':
        pout->lightDown();
        break;

    // change the order of images or delete one
    case 'f':
        rgal.deleteImg();
        pout->readImg( rgal.getImage() );
        break;
    case 'g':
        rgal.moveImgBack();
        pout->readImg( rgal.getImage() );
        break;
    case 'h':
        rgal.moveImgForward();
        pout->readImg( rgal.getImage() );
        break;

    // play & stop
    case 'u':
        if ( rflags.m_playAllowed )
            rflags.m_play = ! rflags.m_play;
        break;
    case 'y':
        rflags.m_direction = ! rflags.m_direction;
        break;
    
    // quit
    case 'q':
        rflags.m_continue = false;
        break;

    default:
        pout->checkShifts();
        break;
    }

    if ( rflags.m_play )
        play( pout, rgal, rflags );
    else 
    {
        pout->printArt();
        nodelay(stdscr, FALSE);
    }

    refresh();
} 

void CEffectManager::play( COutput * pout, CGallery & rgal, CFlags & rflags )
{
    nodelay(stdscr, TRUE);
    // if next or previous image should be loaded
    if ( rflags.m_direction )
        rgal.incIndex();
    else 
        rgal.decIndex();

    pout->readImg ( rgal.getImage() );
    pout->printArt();
}