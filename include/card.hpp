#pragma once

#include "color.hpp"
#include "value.hpp"

/*-----------------------------------------------------------*
 *
 *  Contains the class that represents a Card of the game.
 *
 */

class Card
{
    private:
        Color color;
        Value value;

    public:
        // Creates a Card with the specified parameters
        Card(Color color, Value value);

        // Prints the Card's Color and Value
        void print();

        // Returns the Card's Color
        Color getColor();

        // Returns the Card's Value
        Value getValue();
};
