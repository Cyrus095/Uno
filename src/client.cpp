#include <iostream>    // std::cerr
#include "client.hpp"

/*-----------------------------------------------------------*/

Client::Client(std::string name, sf::IpAddress ip, unsigned short port)
{
    this->name = name;
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
        if (receiveData() and not game->checkGameOver()) {
            clientTurn();
        }
    }

    // Display final information and winner
    display();
    std::cout << std::endl;
    std::cout << "### " << room->getWinner()->getName();
    std::cout << " won!" << std::endl;
}

/*-----------------------------------------------------------*/

bool Client::receiveData()
{
    sf::Packet svData;
    Game *svGame = NULL;
    Room *svRoom = NULL;
    bool myTurn = false;

    if (server.receive(svData) == sf::Socket::Done) {
        svGame = new Game();
        svRoom = new Room();
        if (svData >> *svGame >> *svRoom >> myTurn) {
            delete game;
            delete room;
            game = svGame;
            room = svRoom;
            std::cout << "Data received!" << std::endl;
            display();
        }
        else {
            std::cerr << "Error when receiving data!" << std::endl;
            delete svGame;
            delete svRoom;
            server.disconnect();
            exit(10);
        }
    }
    else {
        std::cout << "Connection lost!" << std::endl;
        exit(400);
    }

    return myTurn;
}

/*-----------------------------------------------------------*/

void Client::clientTurn()
{
    Player *player = room->getPlayer(name);
    sf::Packet data;

    if (player == NULL) {
        std::cerr << "You have not been found in Room!" << std::endl;
        server.disconnect();
        exit(30);
    }

    game->play(player);
    data << *game << *room;
    if (server.send(data) == sf::Socket::Done) {
        std::cout << "Data sent to server!" << std::endl;
    }
    else {
        std::cout << "Connection lost!" << std::endl;
        exit(321);
    }
}

/*-----------------------------------------------------------*/

void Client::display()
{
    Player *player = room->getPlayer(name);

    if (player == NULL) {
        std::cerr << "You have not been found in Room!" << std::endl;
        server.disconnect();
        exit(30);
    }

    room->print();
    player->print();
}
