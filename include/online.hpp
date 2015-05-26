#pragma once

#include "SFML/Network.hpp"
#include "game.hpp"
#include "room.hpp"

/*-----------------------------------------------------------*
 *
 *  Includes code related to both Client and Server classes.
 *
 */

// sf::Packet overload for Room
sf::Packet& operator <<(sf::Packet& packet, const Room& room);
sf::Packet& operator >>(sf::Packet& packet, Room& room);

// sf::Packet overload for Player
sf::Packet& operator <<(sf::Packet& packet, const Player& player);
sf::Packet& operator >>(sf::Packet& packet, Player& player);

// sf::Packet overload for Card
sf::Packet& operator <<(sf::Packet& packet, const Card& card);
sf::Packet& operator >>(sf::Packet& packet, Card& card);
