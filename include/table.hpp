#pragma once

#include <queue>
#include "card.hpp"

/*-----------------------------------------------------------*/

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

        // Returns a pointer to the Table's topmost Card
        Card * getTop();

        // Returns the oldest Card, removing it from the Table
        Card * removeEnd();
};
