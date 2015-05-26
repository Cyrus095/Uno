#pragma once

#include <deque>
#include "player.hpp"

/*-----------------------------------------------------------*/

class Room
{
    private:
        std::deque<Player *> plDeq;  // Players participating in Room
    
    public:
        // Clears memory used by Room
        ~Room();

        // Returns number of Players in Room
        uint size();

        // Inserts Player in Room
        void insert(Player *player);

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
