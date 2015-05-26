#include "client.hpp"

/*-----------------------------------------------------------*/

Client::Client(sf::IpAddress ip, unsigned short port)
{
    myself = new Player("Fulano");

    // Attempt to connect to server
    if (server.connect(ip, port) != sf::Socket::Done) {
        exit(-10);
    }

    loop();
}

/*-----------------------------------------------------------*/

Client::~Client()
{
    server.disconnect();
}

/*-----------------------------------------------------------*/

void Client::loop()
{
/*
    // Send Client's Player data
    sf::Packet data;
    data << myself;
    server.send(myself);

    // Infinite game loop
    while (true) {
        sf::Packet svData;
        Room svRoom;
        Game svGame;

        server.receive(svData);
        if (svData >> svRoom) {
            updateRoom(svRoom);
        }
        if (svData >> svGame) {
            if (updateGame(svGame)) {
                return;  // Game ended
            }
        }
    }
*/
}

/*-----------------------------------------------------------*/

void Client::updateRoom(Room svRoom)
{
    // room = svRoom;
}

/*-----------------------------------------------------------*/

bool Client::updateGame(Game svGame)
{
/*
    game = svGame;

    if (game.ended()) {
        return true;
    }

    if (room.getPlayer(game.getTurn()) == myself) {
        sf::Packet data;

        game.play();
        data << game;
        server.send(data);
    }
*/
    return false;
}
