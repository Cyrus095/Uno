#pragma once

#include <string>

/*-----------------------------------------------------------*
 *
 *  Defines all possible values in the game.
 *
 */

typedef enum value
{
    VALUE_BEGIN,         // Used in loops, represents the first element
    ZERO = VALUE_BEGIN,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    REVERSE,
    SKIP,
    DRAW_TWO,
    WILD,
    WILD_FOUR,
    VALUE_MAX            // Holds the number of elements in the enum
} Value;

/*-----------------------------------------------------------*/

// Definition of ++ operator for Value
Value &operator++(Value &v);
Value  operator++(Value &v, int);

// Definition of -- operator for Value
Value &operator--(Value &v);
Value  operator--(Value &v, int);

/*-----------------------------------------------------------*/

/*
 *  Returns a string corresponding to the value.
 *  For example: SEVEN -> "7".
 *  If the value isn't valid, returns an empty string.
 */
std::string valueToStr(Value value);
