#include <iostream>  // std::cout
#include "room.hpp"

/*-----------------------------------------------------------*/

Room::~Room()
{
    while (not deque.empty()) {
        Player *player = deque.front();
        deque.pop_front();
        delete player;
    }

    deque.clear();
}

/*-----------------------------------------------------------*/

void Room::print()
{
    for (uint i = 0; i < deque.size(); i++) {
        Player *player = deque.at(i);
        std::cout << (i+1) << ") " << player->getName();
        std::cout << " [" << player->handSize() << "]";
        std::cout << std::endl;
    }
}

/*-----------------------------------------------------------*/

uint Room::size()
{
    return deque.size();
}

/*-----------------------------------------------------------*/

bool Room::addPlayer(Player *player)
{
    for (uint i = 0; i < deque.size(); i++) {
        if (deque.at(i)->getName() == player->getName()) {
            return false;
        }
    }

    deque.push_back(player);
    return true;
}

/*-----------------------------------------------------------*/

Player * Room::getPlayer(uint position)
{
    if (position > deque.size()) {
        return NULL;
    }

    return deque.at(position);
}

/*-----------------------------------------------------------*/

Player * Room::getPlayer(std::string name)
{
    for (uint i = 0; i < deque.size(); i++) {
        if (deque.at(i)->getName() == name) {
            return deque.at(i);
        }
    }

    return NULL;
}

/*-----------------------------------------------------------*/

Player * Room::getWinner()
{
    for (uint i = 0; i < deque.size(); i++) {
        if (deque.at(i)->handSize() <= 0) {
            return deque.at(i);
        }
    }

    return NULL;
}

/*-----------------------------------------------------------*/

Player * Room::removePlayer(uint position)
{
    Player *player = NULL;

    if (position <= deque.size()) {
        player = deque.at(position);
        deque.erase(deque.begin() + position);
    }

    return player;
}

/*-----------------------------------------------------------*/

Room& Room::operator =(Room room)
{
    while (this->size() > 0) {
        this->removePlayer(0);
    }

    while (room.size() > 0) {
        Player *player = room.getPlayer(0);
        this->addPlayer(player);
        room.removePlayer(0);
    }

    return *this;
}

/*-----------------------------------------------------------*/

sf::Packet& operator <<(sf::Packet& packet, Room& room)
{
    packet << static_cast<sf::Uint32>(room.size());

    for (uint i = 0; i < room.size(); i++) {
        packet << *room.getPlayer(i);
    }

    return packet;
}

/*-----------------------------------------------------------*/

sf::Packet& operator >>(sf::Packet& packet, Room& room)
{
    sf::Uint32 size;
    packet >> size;

    for (sf::Uint32 i = 0; i < size; i++) {
        Player *player = new Player();
        packet >> *player;
        room.addPlayer(player);
    }

    return packet;
}
