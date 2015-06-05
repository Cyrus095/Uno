#pragma once

#include "game.hpp"
#include "manager.hpp"

/*-----------------------------------------------------------*/

class Server
{
    private:
        std::string name;
        Game *game;
        Manager *manager;
        uint turnCounter = 0;

        sf::SocketSelector selector;
        sf::TcpListener listener;

        void run();

        bool addClient();

        void sendData();

        bool receiveData();

        bool serverTurn();

        void display();

        void updateTurnCount();

    public:
        // Creates a server with the specified port number
        Server(std::string name, unsigned short port);

        // Closes server and clears used memory
        ~Server();
};
