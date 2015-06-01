#include <iostream>  // std::cout
#include "card.hpp"

/*-----------------------------------------------------------*/

Card::Card()
{
    this->color = COLOR_MAX;
    this->value = VALUE_MAX;
}

/*-----------------------------------------------------------*/

Card::Card(Color color, Value value)
{
    this->color = color;
    this->value = value;
}

/*-----------------------------------------------------------*/

void Card::print()
{
    std::cout << colorToStr(color) << " " << valueToStr(value);
    std::cout << std::endl;
}

/*-----------------------------------------------------------*/

void Card::setColor(Color color)
{
    this->color = color;
}

/*-----------------------------------------------------------*/

void Card::setValue(Value value)
{
    this->value = value;
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
