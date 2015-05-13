#include "value.hpp"

/*-----------------------------------------------------------*/

Value &operator++(Value &v)
{
    if (v == VALUE_MAX) {
        throw "Cannot use ++ operator for VALUE_MAX value";
    }

    v = static_cast<Value>(v + 1);

    return v;
}

/*-----------------------------------------------------------*/

Value operator++(Value &v, int)
{
    return static_cast<Value>(++v);
}

/*-----------------------------------------------------------*/

Value &operator--(Value &v)
{
    if (v == VALUE_BEGIN) {
        throw "Cannot use -- operator for VALUE_BEGIN value";
    }

    v = static_cast<Value>(v - 1);

    return v;
}

/*-----------------------------------------------------------*/

Value operator--(Value &v, int)
{
    return static_cast<Value>(--v);
}

/*-----------------------------------------------------------*/

std::string valueToStr(Value value)
{
    switch (value) {
        case ZERO:
            return "0";
        case ONE:
            return "1";
        case TWO:
            return "2";
        case THREE:
            return "3";
        case FOUR:
            return "4";
        case FIVE:
            return "5";
        case SIX:
            return "6";
        case SEVEN:
            return "7";
        case EIGHT:
            return "8";
        case NINE:
            return "9";
        case REVERSE:
            return "Reverse";
        case SKIP:
            return "Skip";
        case DRAW_TWO:
            return "Draw 2";
        case WILD:
            return "\033[31mW\033[33mi\033[32ml\033[34md\033[0m";
        case WILD_FOUR:
            return "\033[31mW\033[33mi\033[32ml\033[34md\033[0m Draw 4";

        default:
            return "";  // Value isn't valid
    }
}
