#include <iostream>        // std::cout
#include "offline.hpp"
#include "randomizer.hpp"

/*-----------------------------------------------------------*/

Offline::Offline(uint numPlayers)
{
    for (uint i = 0; i < numPlayers; i++) {
        Player *player = new Player("");
        game.initPlayer(player);
        room.addPlayer(player);
    }

    turnCounter = randInt(0, room.size());
}

/*-----------------------------------------------------------*/

void Offline::run()
{
    // Possibly, create game window here
    updateGame();
}

/*-----------------------------------------------------------*/

void Offline::updateGame()
{
    Player *current = NULL;

    while (not game.checkGameOver()) {
        current = room.getPlayer(turnCounter);
        game.play(current);
        (game.checkReverse() ? turnCounter ++ : turnCounter--);
        turnCounter %= room.size();
    }

    std::cout << "### " << current->getName() << " wins! ###";
    std::cout << std::endl;
}
