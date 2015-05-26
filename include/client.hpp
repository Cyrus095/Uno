#pragma once

#include "online.hpp"
#include "game.hpp"
#include "room.hpp"

/*-----------------------------------------------------------*/

class Client
{
    private:
        Player *myself;

        sf::TcpSocket server;
        Game *game;
        Room *room;

        // Starts Client's game loop
        void loop();

        // Updates the Client's Room data
        void updateRoom(Room svRoom);

        /*
         *  Updates the Client's game data. If the match has ended,
         *  returns 'true'.
         */
        bool updateGame(Game svGame);

    public:
        // Connects Client to server using the specified values
        Client(sf::IpAddress ip, unsigned short port);

        // Ends connection
        ~Client();
};
