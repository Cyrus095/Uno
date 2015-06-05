#include "table.hpp"

/*-----------------------------------------------------------*/

Table::~Table()
{
    while (not pile.empty()) {
        Card *card = pile.front();
        pile.pop();
        delete card;
    }
}

/*-----------------------------------------------------------*/

uint Table::size()
{
    return pile.size();
}

/*-----------------------------------------------------------*/

void Table::add(Card *card)
{
    return pile.push(card);
}

/*-----------------------------------------------------------*/

Card * Table::getTop()
{
    Card *card = NULL;

    if (not pile.empty()) {
        card = pile.back();
    }

    return card;
}

/*-----------------------------------------------------------*/

Card * Table::removeEnd()
{
    Card *card = NULL;

    if (not pile.empty()) {
        card = pile.front();
        pile.pop();
    }

    return card;
}

/*-----------------------------------------------------------*/

sf::Packet& operator <<(sf::Packet& packet, Table table)
{
    packet << static_cast<sf::Uint32>(table.size());

    while (table.size() > 0) {
        packet << *table.removeEnd();
    }

    return packet;
}

/*-----------------------------------------------------------*/

sf::Packet& operator >>(sf::Packet& packet, Table& table)
{
    sf::Uint32 size;
    packet >> size;

    for (sf::Uint32 i = 0; i < size; i++) {
        Card *card = new Card();
        packet >> *card;
        table.add(card);
    }

    return packet;
}
