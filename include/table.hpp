#pragma once

#include <queue>
#include "card.hpp"

/*-----------------------------------------------------------*
 *
 *  Represents the pile of cards already used by players.
 *
 */

class Table
{
    private:
        std::queue<Card *> pile;

    public:
        // Clears memory used by Table
        ~Table();

        // Returns the number of Cards on the Table
        uint size();

        // Adds the specified Card to the top of the Table
        void add(Card *card);

        /*
         *  Returns the Table's topmost Card.
         *  If empty, returns NULL.
         */
        Card * getTop();

        /*
         *  Returns the oldest Card inserted, removing it
         *  from the Table. If empty, returns NULL.
         */
        Card * removeEnd();
};
