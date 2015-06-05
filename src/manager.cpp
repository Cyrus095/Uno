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

uint Manager::size()
{
    return room->size();
}

/*-----------------------------------------------------------*/

void Manager::add(Player *player, sf::TcpSocket *socket)
{
    room->addPlayer(player);
    dq.push_back(socket);
}

/*-----------------------------------------------------------*/

Player * Manager::getPlayer(uint position)
{
    // Room class can treat the "out of bounds" error
    return room->getPlayer(position); 
}

/*-----------------------------------------------------------*/

Player * Manager::removePlayer(uint position)
{
    // Room class can treat the "out of bounds" error
    return room->removePlayer(position);
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

/*-----------------------------------------------------------*/

sf::Packet& operator <<(sf::Packet& packet, Manager& manager)
{
    return packet << *manager.getRoom();
}
