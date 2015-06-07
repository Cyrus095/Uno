#pragma once

#include "game.hpp"
#include "room.hpp"

/*-----------------------------------------------------------*/

class Offline
{
    private:
        Game *game;
        Room *room;
        uint turnCounter;

        // Runs a game until a Player wins!
        void run();

        // Shows information for Players on their turn
        void display();

    public:
        /*
         *  Creates an offline game, where user's name is the
         *  specified string. Game will have 'numBot' computer
         *  Players.
         */
        Offline(std::string name, uint numBot);

        // Clears data used by Offline object
        ~Offline();
};
