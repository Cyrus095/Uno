#include <iostream>  // std::cout
#include "card.hpp"

/*-----------------------------------------------------------*/

Card::Card(Color color, Value value)
{
    this->color = color;
    this->value = value;
}

/*-----------------------------------------------------------*/

void Card::print()
{
    if (value == WILD or value == WILD_FOUR) {
        std::cout << valueToStr(value) << std::endl;
    }
    else {
        std::cout << colorToStr(color) << " " << valueToStr(value) << std::endl;
    }
}

/*-----------------------------------------------------------*/

Color Card::getColor()
{
    return color;
}

/*-----------------------------------------------------------*/

Value Card::getValue()
{
    return value;
}
