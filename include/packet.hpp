#pragma once

#include "SFML/Network.hpp"
#include "deck.hpp"
#include "table.hpp"
#include "game.hpp"
#include "manager.hpp"

/*-----------------------------------------------------------*
 *
 *  Includes code related to both Client and Server classes.
 *
 */

// sf::Packet overload for Card
sf::Packet& operator <<(sf::Packet& packet, Card& card);
sf::Packet& operator >>(sf::Packet& packet, Card& card);

// sf::Packet overload for Player
sf::Packet& operator <<(sf::Packet& packet, Player& player);
sf::Packet& operator >>(sf::Packet& packet, Player& player);

// sf::Packet overload for Deck
sf::Packet& operator <<(sf::Packet& packet, Deck deck);
sf::Packet& operator >>(sf::Packet& packet, Deck& deck);

// sf::Packet overload for Table
sf::Packet& operator <<(sf::Packet& packet, Table table);
sf::Packet& operator >>(sf::Packet& packet, Table& table);

// sf::Packet overload for Room
sf::Packet& operator <<(sf::Packet& packet, Room& room);
sf::Packet& operator >>(sf::Packet& packet, Room& room);

// sf::Packet overload for Manager
sf::Packet& operator <<(sf::Packet& packet, Manager& manager);

// sf::Packet overload for Game
sf::Packet& operator <<(sf::Packet& packet, Game& game);
sf::Packet& operator >>(sf::Packet& packet, Game& game);
