#include "packet.hpp"
#include <iostream>

/*-----------------------------------------------------------*/

sf::Packet& operator <<(sf::Packet& packet, Card& card)
{
    return packet << (uint) card.getColor() << (uint) card.getValue();
}

/*-----------------------------------------------------------*/

sf::Packet& operator >>(sf::Packet& packet, Card& card)
{
    uint color, value;

    packet >> color >> value;
    card.setColor((Color) color);
    card.setValue((Value) value);

    return packet;
}

/*-----------------------------------------------------------*/

sf::Packet& operator <<(sf::Packet& packet, Player& player)
{
    packet << player.getName();
    packet << static_cast<sf::Uint32>(player.handSize());

    for (uint i = 0; i < player.handSize(); i++) {
        packet << *player.getCard(i);
    }

    return packet;
}

/*-----------------------------------------------------------*/

sf::Packet& operator >>(sf::Packet& packet, Player& player)
{
    std::string name;
    packet >> name;
    player.setName(name);

    sf::Uint32 size;
    packet >> size;

    for (sf::Uint32 i = 0; i < size; i++) {
        Card *card = new Card();
        packet >> *card;
        player.addCard(card);
    }

    return packet;
}

/*-----------------------------------------------------------*/

sf::Packet& operator <<(sf::Packet& packet, Deck deck)
{
    packet << static_cast<sf::Uint32>(deck.size());

    while (deck.size() > 0) {
        packet << *deck.draw();
    }

    return packet;
}

/*-----------------------------------------------------------*/

sf::Packet& operator >>(sf::Packet& packet, Deck& deck)
{
    sf::Uint32 size;
    packet >> size;

    for (sf::Uint32 i = 0; i < size; i++) {
        Card *card = new Card();
        packet >> *card;
        deck.insert(card);
    }
    deck.reverse();

    return packet;
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

/*-----------------------------------------------------------*/

sf::Packet& operator <<(sf::Packet& packet, Manager& manager)
{
    return packet << *manager.getRoom();
}

/*-----------------------------------------------------------*/

sf::Packet& operator <<(sf::Packet& packet, Game& game)
{
    packet << *game.getDeck() << *game.getTable();
    packet << game.checkSkip() << game.checkReverse();
    packet << game.getDrawCount() << game.checkGameOver();

    return packet;
}

/*-----------------------------------------------------------*/

sf::Packet& operator >>(sf::Packet& packet, Game& game)
{
    Deck *deck = new Deck();
    Table *table = new Table();
    bool skipped, reversed, gameOver;
    uint drawCount;

    packet >> *deck;
    packet >> *table;
    packet >> skipped >> reversed;
    packet >> drawCount >> gameOver;

    game.setDeck(deck);
    game.setTable(table);

    game.setSkip(skipped);
    game.setReverse(reversed);
    game.setDrawCount(drawCount);
    game.setGameOver(gameOver);

    return packet;
}
