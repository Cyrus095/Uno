#pragma once

#include <deque>
#include "card.hpp"

/*-----------------------------------------------------------*
 *
 *  Holds the class that represents an in-game player.
 *
 */

class Player
{
    private:
        std::string name;
        std::deque<Card *> hand;

    public:
        /*
         *  Creates a Player with an empty string as name.
         *  Use with caution!
         */
        Player();

        // Creates a Player with the specified name
        Player(std::string name);

        // Clears memory used by Player
        ~Player();

        // Returns the number of Cards the Player holds
        uint handSize();

        // Prints all Cards owned by Player
        void printHand();

        // Adds the specified Card to the Player's hand
        void addCard(Card *card);

        /*
         *  Returns the Card in the specified position.
         *  If position is out of bounds, returns NULL.
         */
        Card * getCard(uint position);

        /*
         *  Removes and returns the Card in the specified position.
         *  If position is out of bounds, returns NULL.
         */
        Card * removeCard(uint position);

        // Sets the Player's name to the specified argument
        void setName(std::string name);

        // Returns the Player's name
        std::string getName();
};

// Operators for SFML Packets
sf::Packet& operator <<(sf::Packet& packet, Player& player);
sf::Packet& operator >>(sf::Packet& packet, Player& player);
