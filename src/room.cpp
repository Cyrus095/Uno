#include "room.hpp"

/*-----------------------------------------------------------*/

Room::~Room()
{
    for (uint i = 0; i < plDeq.size(); i++) {
        delete plDeq.at(i);
    }

    plDeq.clear();
}

/*-----------------------------------------------------------*/

uint Room::size()
{
    return plDeq.size();
}

/*-----------------------------------------------------------*/

void Room::insert(Player *player)
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
    for (uint i = this->size(); i >= 0; i--) {
        this->removePlayer(0);
    }

    for (uint i = 0; i < a.size(); i++) {
        this->insert(a.getPlayer(i));
    }
}
