#include "color.hpp"

/*-----------------------------------------------------------*/

Color &operator++(Color &c)
{
    if (c == COLOR_MAX) {
        throw "Cannot use ++ operator for COLOR_MAX value";
    }

    c = static_cast<Color>(c + 1);

    return c;
}

/*-----------------------------------------------------------*/

Color operator++(Color &c, int)
{
    return static_cast<Color>(++c);
}

/*-----------------------------------------------------------*/

Color &operator--(Color &c)
{
    if (c == COLOR_BEGIN) {
        throw "Cannot use -- operator for COLOR_BEGIN value";
    }

    c = static_cast<Color>(c - 1);

    return c;
}

/*-----------------------------------------------------------*/

Color operator--(Color &c, int)
{
    return static_cast<Color>(--c);
}

/*-----------------------------------------------------------*/

std::string colorToStr(Color color)
{
    switch (color) {
        case RED:
            return "\033[31mRed\033[0m";
        case YELLOW:
            return "\033[33mYellow\033[0m";
        case GREEN:
            return "\033[32mGreen\033[0m";
        case BLUE:
            return "\033[34mBlue\033[0m";
        default:
            return "";  // Color isn't valid
    }
}
