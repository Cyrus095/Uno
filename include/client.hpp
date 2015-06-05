#pragma once

#include "game.hpp"
#include "room.hpp"

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

        /*
         *  Receives data from Server. If it is the Client's turn,
         *  returns 'true'.
         */
        bool receiveData();

        // Updates the Client's Room data
        void updateRoom(Room svRoom);

        // Makes client play his turn, sending data to server afterwards
        void clientTurn();

        // Displays information about the Client
        void display();

    public:
        // Connects Client to server using the specified values
        Client(std::string name, sf::IpAddress ip, unsigned short port);

        // Ends connection
        ~Client();
};
