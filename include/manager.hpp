#pragma once

#include "room.hpp"

/*-----------------------------------------------------------*
 *
 *  Class for easier server control over players and sockets.
 *
 */

class Manager
{
    private:
        Room *room;
        std::deque<sf::TcpSocket *> dq;

    public:
        // Initializes a Manager object
        Manager();

        // Clears memory used by Manager
        ~Manager();

        // Returns number of Players/sockets contained in Manager
        uint size();

        // Adds a Player with the specified socket to the Manager
        void add(Player *player, sf::TcpSocket *socket);

        /*
         *  Returns the Player in the specified position.
         *  If position is out of bounds, returns NULL.
         */
        Player * getPlayer(uint position);

        /*
         *  Removes and returns the Player in the specified position.
         *  If position is out of bounds, returns NULL.
         */
        Player * removePlayer(uint position);

        /*
         *  Returns the socket in the specified position.
         *  If position is out of bounds, returns NULL.
         */
        sf::TcpSocket * getSocket(uint position);

        /*
         *  Removes and returns the socket in the specified position.
         *  If position is out of bounds, returns NULL.
         */
        sf::TcpSocket * removeSocket(uint position);

        /* 
         * -------------------------------------
         *  Below methods are to be used only
         *  for Packet sending and receiving!
         * -------------------------------------
         */

        // Sets the Manager's Room as the specified argument
        void setRoom(Room *r);

        // Returns Room used in Manager
        Room * getRoom();
};

// Operators for SFML Packets
sf::Packet& operator <<(sf::Packet& packet, Manager& manager);
