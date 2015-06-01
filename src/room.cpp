#include <iostream>  // std::cout
#include "room.hpp"

/*-----------------------------------------------------------*/

Room::~Room()
{
    while (not plDeq.empty()) {
        Player *player = plDeq.front();
        plDeq.pop_front();
        delete player;
    }

    plDeq.clear();
}

/*-----------------------------------------------------------*/

void Room::print()
{
    for (uint i = 0; i < plDeq.size(); i++) {
        Player *player = plDeq.at(i);
        std::cout << (i+1) << ") " << player->getName();
        std::cout << " [" << player->handSize() << "]";
        std::cout << std::endl;
    }
}

/*-----------------------------------------------------------*/

uint Room::size()
{
    return plDeq.size();
}

/*-----------------------------------------------------------*/

void Room::addPlayer(Player *player)
{
    plDeq.push_back(player);
}

/*-----------------------------------------------------------*/

Player * Room::getPlayer(uint position)
{
    if (position > plDeq.size()) {
        return NULL;
    }

    return plDeq.at(position);
}

/*-----------------------------------------------------------*/

Player * Room::removePlayer(uint position)
{
    Player *player = NULL;

    if (position <= plDeq.size()) {
        player = plDeq.at(position);
        plDeq.erase(plDeq.begin() + position);
    }

    return player;
}

/*-----------------------------------------------------------*/

Room& Room::operator =(Room a)
{
    while (this->size() > 0) {
        this->removePlayer(0);
    }

    while (a.size() > 0) {
        Player *player = a.getPlayer(0);
        this->addPlayer(player);
        a.removePlayer(0);
    }

    return *this;
}
