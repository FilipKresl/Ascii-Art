#include <ncurses.h>

#include "CMessages.hpp"

using namespace std;

void CMessages::ncursInit()
{
    initscr();
    cbreak();
    noecho();
}
void CMessages::printHelp()
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
    getch();
    endwin();
}
void CMessages::printError()
{        
    ncursInit();
    printw( "--WRONG INPUT--\n" );
    printw( "type:\n" );
    printw( "   ./kreslfil -h\n" );
    printw( "for help\n" );

    refresh();
    getch();
    endwin();
}
