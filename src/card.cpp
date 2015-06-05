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
    std::string space;

    color == COLOR_MAX ? space = "" : space = " ";
    std::cout << colorToStr(color) << space << valueToStr(value);
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

/*-----------------------------------------------------------*/

sf::Packet& operator <<(sf::Packet& packet, Card& card)
{
    return packet << (uint) card.getColor() << (uint) card.getValue();
}

/*-----------------------------------------------------------*/

sf::Packet& operator >>(sf::Packet& packet, Card& card)
{
    uint color, value;

    packet >> color >> value;
    card.setColor((Color) color);
    card.setValue((Value) value);

    return packet;
}
