/**
 * @file CTests.hpp
 * @brief file for class CTests, asserts a few methods
 */
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <assert.h>

#pragma once

using namespace std;

/**
 * @brief runs predefined scenarios and asserts expected results
 */
class CTests
{
public:
    /**
     * @brief construct a new CTests object and automatically launches tests
     */
    CTests();
private:
    /**
     * @brief checks if BMP and TGA load fill PixelMap correctly  
     */
    void testLoading();
    /**
     * @brief checks if output-effect method works correctly
     */
    void testLights();
};