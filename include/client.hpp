#pragma once

#include "game.hpp"
#include "room.hpp"
#include "packet.hpp"

/*-----------------------------------------------------------*/

class Client
{
    private:
        std::string name;

        Game *game;
        Room *room;

        sf::TcpSocket server;

        // Starts Client's game loop
        void run();

        // Updates the Client's Room data
        void updateRoom(Room svRoom);

        // Makes client play his turn, sending data to server afterwards
        void clientTurn();

    public:
        // Connects Client to server using the specified values
        Client(sf::IpAddress ip, unsigned short port);

        // Ends connection
        ~Client();
};
