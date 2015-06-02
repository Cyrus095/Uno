#include "manager.hpp"

/*-----------------------------------------------------------*/

Manager::Manager()
{
    room = new Room();
}

/*-----------------------------------------------------------*/

Manager::~Manager()
{
    delete room;

    while (not dq.empty()) {
        sf::TcpSocket *socket = dq.front();
        dq.pop_front();
        delete socket;
    }

    dq.clear();    
}

/*-----------------------------------------------------------*/

void Manager::add(Player *player, sf::TcpSocket *socket)
{
    room->addPlayer(player);
    dq.push_back(socket);
}

/*-----------------------------------------------------------*/

uint Manager::size()
{
    return room->size();
}

/*-----------------------------------------------------------*/

Player * Manager::getPlayer(uint position)
{
    // Room class can treat the "out of range" error
    return room->getPlayer(position); 
}

/*-----------------------------------------------------------*/

sf::TcpSocket * Manager::getSocket(uint position)
{
    if (position > dq.size()) {
        return NULL;
    }

    return dq.at(position);
}

/*-----------------------------------------------------------*/

sf::TcpSocket * Manager::removeSocket(uint position)
{
    sf::TcpSocket *socket = NULL;;

    if (position <= dq.size()) {
        socket = dq.at(position);
        dq.erase(dq.begin() + position);
    }

    return socket;
}

/*-----------------------------------------------------------*/

void Manager::setRoom(Room *r)
{
    delete this->room;
    room = r;
}

/*-----------------------------------------------------------*/

Room * Manager::getRoom()
{
    return room;
}
