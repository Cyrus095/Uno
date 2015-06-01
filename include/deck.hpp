#pragma once

#include <deque>
#include "card.hpp"

/*-----------------------------------------------------------*
 *
 *  Holds the class that represents the Uno deck.
 *
 */

class Deck
{
    private:
        std::deque<Card *> dq;

    public:
        // Initializes the Deck with all possible Cards in Uno
        Deck(bool init = false);

        // Clears memory used by Deck
        ~Deck();

        // Returns the remaining number of Cards in the Deck
        uint size();

        /* 
         *  Returns the topmost Card, removing it from the Deck.
         *  If Deck is empty, returns NULL.
         */
        Card * draw();

        // Inserts a Card at the bottom of the Deck
        void insert(Card *card);

        // Reverses deck order (first card becomes last and so on forth)
        void reverse();

        void print();

        // Shuffles Cards in the Deck the specified number of times
        void shuffle(uint times);
};
