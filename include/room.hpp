#pragma once

#include <deque>
#include "player.hpp"

/*-----------------------------------------------------------*
 *
 *  Defines the Room class, responsible for storing all Players.
 *
 */

class Room
{
    private:
        std::deque<Player *> plDeq;
    
    public:
        // Clears memory used by Room
        ~Room();

        // Returns number of Players in Room
        uint size();

        // Prints names of all Players inside Room
        void print();

        // Inserts Player in Room
        void addPlayer(Player *player);

        /*
         *  Returns the Player in the specified position.
         *  If position is out of bounds, returns NULL.
         */
        Player * getPlayer(uint position);

        /*
         *  Removes and returns the Player in the specified position.
         *  If position is out of bounds, returns NULL.
         */
        Player * removePlayer(uint position);

        Room& operator =(Room a);
};
