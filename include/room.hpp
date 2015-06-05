#pragma once

#include <deque>
#include "player.hpp"

/*-----------------------------------------------------------*
 *
 *  Defines the Room class, responsible for storing Players.
 *
 */

class Room
{
    private:
        std::deque<Player *> deque;
    
    public:
        // Clears memory used by Room
        ~Room();

        // Returns number of Players in Room
        uint size();

        /*
         *  Prints names of Players and their respective
         *  hand size.
         */
        void print();

        /*
         *  Inserts Player in Room if there is no other 
         *  Player with the same name. If successful,
         *  returns 'true'.  
         */  
        bool addPlayer(Player *player);

        /*
         *  Returns the Player in the specified position.
         *  If position is out of bounds, returns NULL.
         */
        Player * getPlayer(uint position);

        /*
         *  Returns the Player with the specified name.
         *  If not found, returns NULL;
         */
        Player * getPlayer(std::string name);

        // Returns the first Player detected with no Cards
        Player * getWinner();

        /*
         *  Removes and returns the Player in the specified position.
         *  If position is out of bounds, returns NULL.
         */
        Player * removePlayer(uint position);

        Room& operator =(Room room);
};

// Operators for SFML Packets
sf::Packet& operator <<(sf::Packet& packet, Room& room);
sf::Packet& operator >>(sf::Packet& packet, Room& room);
