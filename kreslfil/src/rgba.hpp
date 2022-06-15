/**
 * @file rgba.hpp
 * @brief file for struct rgba, info about one colorful pixel
 * 
 */
#pragma once

#include <stdint.h>

/**
 * @brief stores info about one colorful pixel
 */
struct rgba
{
    /**
     * @brief 4 Bytes - RGBA
     */
    uint8_t b, g, r, a;
};