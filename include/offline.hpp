#pragma once

#include "game.hpp"
#include "room.hpp"

/*-----------------------------------------------------------*/

class Offline
{
    private:
        Game game;
        Room room;
        uint turnCounter;

    public:
        Offline(uint numPlayers);

        void run();

        void updateGame();
};
