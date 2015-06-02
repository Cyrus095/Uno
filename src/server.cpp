#include <iostream>    // std::cout
#include "server.hpp"
#include "packet.hpp"

/*-----------------------------------------------------------*/

Server::Server(std::string name, unsigned short port)
{
    this->name = name;
    game = new Game(true);
    manager = new Manager();

    // Initialize Server's Player
    Player *myself = new Player(name);
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

    // Display final information and winner
    display();
    std::cout << std::endl;
    std::cout << "### " << manager->getRoom()->getWinner()->getName();
    std::cout << " won!" << std::endl;
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

    display();
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
            else {
                std::cout << "Client " << manager->getRoom()->removePlayer(i)->getName();
                std::cout << " disconnected!" << std::endl;
                sf::TcpSocket *socket = manager->removeSocket(i);
                selector.remove(*socket);
                if (manager->size() <= 1) {
                    std::cout << "Not enough players!" << std::endl;
                    exit(42);
                }
                if (turnCounter == i) {
                    (game->checkReverse() ? turnCounter ++ : turnCounter--);
                    turnCounter %= manager->size();
                }
                return true;
            }
        }
    }

    return false;
}

/*-----------------------------------------------------------*/

bool Server::serverTurn()
{
    if (turnCounter == 0) {
        game->play(manager->getRoom()->getPlayer(name));
        (game->checkReverse() ? turnCounter ++ : turnCounter--);
        turnCounter %= manager->size();
        return true;
    }

    return false;
}

/*-----------------------------------------------------------*/

void Server::display()
{
    Player *player = manager->getRoom()->getPlayer(name);

    if (player == NULL) {
        std::cerr << "You have not been found in Room!" << std::endl;
        exit(30);
    }

    manager->getRoom()->print();
    player->print();
}
