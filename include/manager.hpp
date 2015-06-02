#pragma once

#include "SFML/Network.hpp"
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

        // Adds a Player with the specified socket to the Manager
        void add(Player *player, sf::TcpSocket *socket);

        // Returns number of Players/sockets contained in Manager
        uint size();

        /*
         *  Returns the Player in the specified position.
         *  If position is out of bounds, returns NULL.
         */
        Player * getPlayer(uint position);

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

        // Sets the Manager's Room as the specified argument
        void setRoom(Room *r);

        // Returns Room used in Manager
        Room * getRoom();
};
