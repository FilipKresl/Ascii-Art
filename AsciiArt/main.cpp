/**
 * @file main.cpp
 * @brief Main entry point. 
 */

// #include "cmdline.hpp"
// #include "gallery.hpp"
// #include "image.hpp"
// #include "bmpimage.hpp"
// #include "output.hpp"
// #include "asciiart.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#define D if(1) cout

using namespace std;

// typedef bitset<8> BYTE;

struct rgba
{
    uint8_t b, g, r, a;
};

void imgFill( vector<rgba> & img )
{
    rgba Apix = {0,0,0,0};
    img.push_back( Apix );
    rgba Bpix = {32,64,96,255};
    img.push_back( Bpix );
    rgba Cpix = {255,255,255,255};
    img.push_back( Cpix );
    rgba Dpix = {0,255,127,255};
    img.push_back( Dpix );
}
void imgPrint( vector<rgba> & img )
{
    for (int i = 0; i < img.size(); i++)
    {
        cout << hex << setfill('0') << setw(2) << (int) img[i].b << " ";
        cout << hex << setfill('0') << setw(2) << (int) img[i].g << " ";
        cout << hex << setfill('0') << setw(2) << (int) img[i].r << " ";
        cout << hex << setfill('0') << setw(2) << (int) img[i].a;
        cout << endl;
    }
    
}
void convertGray( vector<rgba> & img, vector<uint8_t> & buffer )
{
    int sum = 0;
    for (int i = 0; i < img.size(); i++)
    {
        sum = ( img[i].b + img[i].g + img[i].r ) / 3;
        buffer.push_back( sum );
    } 
}
void bufferPrint( vector<uint8_t> & buffer )
{
    for (int i = 0; i < buffer.size(); i++)
    {
        cout << hex << setfill('0') << setw(2) << (int) buffer[i] << " | ";
    }
    cout << endl;
}
void palleteFill( vector<char> & pallete )
{
    pallete.push_back( ' ' );
    pallete.push_back( '.' );
    pallete.push_back( 'i' );
    pallete.push_back( 'w' );
    pallete.push_back( '2' );
    pallete.push_back( '8' );
    pallete.push_back( '@' );
}
void printPallete( vector<char> & pallete )
{
    cout << "pallete >";
    for (int i = 0; i < pallete.size(); i++)
    {
        cout << pallete[i];
    }
    cout << "<" << endl;
    
}
char convertAscii( vector<uint8_t> & buffer, vector<char> & pallete, int index )
{
    int charSize = 256;
    int palSize = pallete.size();
    double res = ( (double) buffer[index] / charSize ) * palSize;
    // cout << "           res = " << res << endl;
    return pallete[res];
}
void printArt( vector<uint8_t> & buffer, vector<char> & pallete )
{
    int rows = 2;
    int cols = 2;
    cout << "ASCII - ART" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int k = 0; k < cols; k++)
        {
            int index = i*cols + k;
            cout << convertAscii( buffer, pallete, index );
        }
        cout << endl;
    }   
}
int main ( int argc, char** argv )
{
    vector<rgba> img;
    imgFill( img );
    imgPrint( img );
    vector<uint8_t> buffer;
    convertGray( img, buffer );
    bufferPrint( buffer );
    vector<char> pallete;
    palleteFill( pallete );
    printPallete( pallete );
    printArt( buffer, pallete );
    
    // D << "OK" << endl;

    return 0;
}