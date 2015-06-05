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
        std::deque<Card *> deque;

    public:
        /*
         *  If 'init' is 'true', initializes the Deck with 
         *  default Cards in Uno.
         */
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

        /*
         *  Reverses Card order in Deck; first Card becomes last
         *  and so on forth.
         */
        void reverse();

        // Shuffles Cards in the Deck the specified number of times
        void shuffle(uint times);
};

// Operators for SFML Packets
sf::Packet& operator <<(sf::Packet& packet, Deck deck);
sf::Packet& operator >>(sf::Packet& packet, Deck& deck);
