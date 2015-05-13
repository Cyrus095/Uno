#pragma once

#include <deque>
#include "card.hpp"

/*-----------------------------------------------------------*/

class Deck
{
    private:
        std::deque<Card *> dq;

    public:
        // Initializes the Deck with all possible Cards
        Deck();

        // Clears memory used by Deck
        ~Deck();

        // Returns the remaining number of Cards in the Deck
        uint size();

        // Returns the topmost Card, removing it from the Deck
        Card * draw();

        // Inserts a Card at the bottom of the Deck
        void insert(Card *card);

        // Shuffles Cards in the Deck the specified number of times
        void shuffle(uint times);
};
