#include <iostream>    // std::cout
#include "server.hpp"
#include "packet.hpp"

/*-----------------------------------------------------------*/

Server::Server(unsigned short port)
{
    game = new Game(true);
    manager = new Manager();

    // Initialize Server's Player
    Player *myself = new Player("Mr. Server");
    game->initPlayer(myself);
    manager->add(myself, NULL);

    // Create a socket to listen to new connections
    if (listener.listen(port) != sf::Socket::Done) {
        exit(200);
    }
    selector.add(listener);

    std::cout << "Server has been created!" << std::endl;
    run();
}

/*-----------------------------------------------------------*/

Server::~Server()
{
    delete game;
    delete manager;
    listener.close();
    selector.clear();
}

/*-----------------------------------------------------------*/

void Server::run()
{
    while (not game->checkGameOver()) {
        manager->getRoom()->print();
        if (selector.wait()) {
            if (selector.isReady(listener)) {
                if (addClient()) {
                    sendData();
                }
            }
            else {
                if (manager->size() >= 2 and receiveData()) {
                    sendData();
                }
            }
        }

        if (manager->size() >= 2 and (not game->checkGameOver()) and serverTurn()) {
            sendData();
        }
    }

    std::cout << "GAME HAS ENDED!!!\n";
}

/*-----------------------------------------------------------*/

bool Server::addClient()
{
    sf::TcpSocket *client = new sf::TcpSocket;

    if (listener.accept(*client) == sf::Socket::Done) {
        sf::Packet clName;
        std::string name;

        client->receive(clName);
        if (clName >> name) {
            Player *player = new Player(name);
            manager->add(player, client);
            selector.add(*client);
            std::cout << name << " connected to server!" << std::endl;
            game->initPlayer(player);
            return true;
        }
    }

    delete client;
    return false;
}

/*-----------------------------------------------------------*/

void Server::sendData()
{
    for (uint i = 0; i < manager->size(); i++) {
        sf::TcpSocket *client = manager->getSocket(i);
        if (client == NULL) {
            continue;
        }
        sf::Packet data;
        data << *game << *manager << (i == turnCounter);
        if (client->send(data) == sf::Socket::Done) {
        }
        else {
            std::cerr << "Error when sending info to client!" << std::endl;
        }
    }
    std::cout << "Information sent to all clients!\n";
}

/*-----------------------------------------------------------*/

bool Server::receiveData()
{
    Game *clGame = NULL;
    Room *clRoom = NULL;

    for (uint i = 0; i < manager->size(); i++) {
        sf::TcpSocket *client = manager->getSocket(i);
        if (client == NULL) {
            continue;
        }
        if (selector.isReady(*client)) {
            std::cout << "Receiving data from " << manager->getPlayer(i)->getName() << std::endl;
            sf::Packet data;
            if (client->receive(data) == sf::Socket::Done) {
                clGame = new Game();
                clRoom = new Room();
                if (data >> *clGame >> *clRoom) {
                    delete game;
                    game = clGame;
                    manager->setRoom(clRoom);
                    (game->checkReverse() ? turnCounter ++ : turnCounter--);
                    turnCounter %= manager->size();
                    return true;
                }
                else {
                    delete clGame;
                    delete clRoom;
                }
            }
        }
    }

    return false;
}

/*-----------------------------------------------------------*/

bool Server::serverTurn()
{
    if (turnCounter == 0) {
        game->play(manager->getPlayer(0));
        (game->checkReverse() ? turnCounter ++ : turnCounter--);
        turnCounter %= manager->size();
        return true;
    }

    return false;
}
