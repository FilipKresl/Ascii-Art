/**
 * @file CMessages.hpp
 * @brief file for class CMessages, handles non-art output
 */
#pragma once

using namespace std;

/**
 * @brief class for printing non-art output
 */
class CMessages
{
public:
    /**
     * @brief initializes screen for ncurses
     */
    void ncursInit() const;
    /**
     * @brief prints help message
     */
    void printHelp() const;
    /**
     * @brief prints error message
     */
    void printError() const;
};

