#include <iostream>        // std::cout
#include "offline.hpp"
#include "randomizer.hpp"

/*-----------------------------------------------------------*/

Offline::Offline(std::string name, uint numBot)
{
    game = new Game(true);
    room = new Room();

    Player *myself = new Player(name);
    game->initPlayer(myself);
    room->addPlayer(myself);

    for (uint i = 0; i < numBot; i++) {
        Player *player = new Player("Bot " + std::to_string(i+1));
        game->initPlayer(player);
        room->addPlayer(player);
    }

    turnCounter = randInt(0, room->size());
    run();
}

/*-----------------------------------------------------------*/

Offline::~Offline()
{
    delete game;
    delete room;
}

/*-----------------------------------------------------------*/

void Offline::run()
{
    Player *current = NULL;

    while (not game->checkGameOver()) {
        display();
        current = room->getPlayer(turnCounter);
        game->play(current);
        (game->checkReverse() ? turnCounter ++ : turnCounter--);
        turnCounter %= room->size();
    }

    std::cout << "### " << current->getName() << " wins! ###";
    std::cout << std::endl;
}

/*-----------------------------------------------------------*/

void Offline::display()
{
    Player *player = room->getPlayer(turnCounter);

    system("clear");
    room->print();
    game->print();
    player->printHand();
}
