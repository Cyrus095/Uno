#include <iostream>    // std::cerr
#include "client.hpp"

/*-----------------------------------------------------------*/

Client::Client(sf::IpAddress ip, unsigned short port)
{
    name = "Mister Client";
    game = new Game();
    room = new Room();

    // Attempt to connect to server
    if (server.connect(ip, port) != sf::Socket::Done) {
        std::cerr << "Couldn't connect to server!" << std::endl;
        exit(-10);
    }

    run();
}

/*-----------------------------------------------------------*/

Client::~Client()
{
    server.disconnect();
    delete game;
    delete room;
}

/*-----------------------------------------------------------*/

void Client::run()
{
    // Send Client's Player data
    sf::Packet clData;
    clData << name;
    server.send(clData);

    // Infinite game loop
    while (not game->checkGameOver()) {
        sf::Packet svData;
        Game *svGame = NULL;
        Room *svRoom = NULL;
        bool myTurn;

        if (server.receive(svData) == sf::Socket::Done) {
            svGame = new Game();
            svRoom = new Room();
            if (svData >> *svGame >> *svRoom >> myTurn) {
                delete game;
                delete room;
                game = svGame;
                room = svRoom;
                room->print();
                std::cout << "Data received!\n";
                if (myTurn and not game->checkGameOver()) {
                    clientTurn();
                }
            }
            else {
                delete svGame;
                delete svRoom;
            }
        }
    }

    // Search Room for winner
}

/*-----------------------------------------------------------*/

void Client::clientTurn()
{
    Player *player = NULL;
    sf::Packet data;

    for (uint i = 0; i < room->size(); i++) {
        if (room->getPlayer(i)->getName() == name) {
            player = room->getPlayer(i);
        }
    }

    if (player == NULL) {
        std::cerr << "You have not been found in Room!" << std::endl;
        exit(30);
    }

    game->play(player);
    data << *game << *room;
    if (server.send(data) == sf::Socket::Done) {
        std::cout << "Data sent to server!" << std::endl;
    }
}
