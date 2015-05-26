#include "online.hpp"

/*-----------------------------------------------------------*/

sf::Packet& operator <<(sf::Packet& packet, Room& room)
{
    packet << static_cast<sf::Uint32>(room.size());

    for (uint i = 0; i < room.size(); i++) {
        packet << room.getPlayer(i);
    }

    return packet;
}

/*-----------------------------------------------------------*/

sf::Packet& operator >>(sf::Packet& packet, Room& room)
{
    sf::Uint32 size;
    packet >> size;

    for (sf::Uint32 i = 0; i < size; i++) {
        Player *player;
        packet >> *player;
        room.insert(player);
    }

    return room;
}

/*-----------------------------------------------------------*/

sf::Packet& operator <<(sf::Packet& packet, Player& player)
{
    packet << player.getName();
    packet << static_cast<sf::Uint32>(player.size());

    for (uint i = 0; i < player.size(); i++) {
        packet << player.getCard(i);
    }

    return packet;
}

/*-----------------------------------------------------------*/

sf::Packet& operator >>(sf::Packet& packet, Player& player)
{
    sf::Uint32 size;
    packet >> size;

    for (sf::Uint32 i = 0; i < size; i++) {
        Card *card;
        packet >> *card;
        player.addCard(card);
    }

    return player;
}

/*-----------------------------------------------------------*/

sf::Packet& operator <<(sf::Packet& packet, Card& card)
{
    return packet << card.getColor() << card.getValue();
}

/*-----------------------------------------------------------*/

sf::Packet& operator >>(sf::Packet& packet, Card& card)
{
    return card;
}
