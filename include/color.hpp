#pragma once

#include <string>

/*-----------------------------------------------------------*
 *
 *  Defines all possible colors in the game.
 *
 */

typedef enum color
{
    COLOR_BEGIN,        // Used in loops, represents the first element
    RED = COLOR_BEGIN,
    YELLOW,
    GREEN,
    BLUE,
    COLOR_MAX           // Holds the number of elements in the enum
} Color;

/*-----------------------------------------------------------*/

// Definition of ++ operator for Color
Color &operator++(Color &c);
Color  operator++(Color &c, int);

// Definition of -- operator for Color
Color &operator--(Color &c);
Color  operator--(Color &c, int);

/*-----------------------------------------------------------*/

/*
 *  Returns a string corresponding to the color.
 *  For example: RED -> "Red".
 *  If the color isn't valid, returns an empty string.
 */
std::string colorToStr(Color color);
