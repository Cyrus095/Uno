#pragma once

#include "color.hpp"
#include "value.hpp"
#include "SFML/Network.hpp"

/*-----------------------------------------------------------*
 *
 *  Contains the class that represents a card of the game.
 *
 */

class Card
{
    private:
        Color color;
        Value value;

    public:
        /*
         *  Creates an empty Card with COLOR_MAX and VALUE_MAX
         *  attributes. Use with caution!
         */
        Card();

        // Creates a Card with the specified parameters
        Card(Color color, Value value);

        // Prints the Card's Color and Value
        void print();

        // Sets the Card's Color as the specified argument
        void setColor(Color color);

        // Sets the Card's Value as the specified argument
        void setValue(Value value);

        // Returns the Card's Color
        Color getColor();

        // Returns the Card's Value
        Value getValue();
};

// Operators for SFML Packets
sf::Packet& operator <<(sf::Packet& packet, Card& card);
sf::Packet& operator >>(sf::Packet& packet, Card& card);
