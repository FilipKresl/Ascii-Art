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

using namespace std;

int main ( int argc, char ** argv )
{
    cout << "main {" << endl;
    vector<string> paths = {"assets/img/3x3.bmp", "assets/img/10x3.bmp"};
    // vector<string> paths = {"assets/img/3x3.bmp"};
    
    cout << "check" << endl;

    CGallery gal( paths );

    cout << "} main" << endl;
    return 0;
}
