/**
 * @file main.cpp
 * @brief Main entry point. 
 */

#include "cmdline.hpp"
#include "gallery.hpp"
#include "image.hpp"
#include "bmpimage.hpp"
#include "output.hpp"
#include "asciiart.hpp"

int main ( int argc, char** argv )
{
    // tbd
    CCommandLine cmd( argc, argv );  
    // tbd
    CGallery gal();
    // tbd
    string fileName = "./filename.bmp";
    CImage * pimg = new CBmpImage( fileName );
    // tbd
    CAsciiArt ascout();
    // tbd

    return 0;
}