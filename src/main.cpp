#include <iostream>  // std::cout
#include "game.hpp"

// Shows how to use the program, leaving if afterwards
static void usage(char const *name);

/*-----------------------------------------------------------*/

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        usage(argv[0]);
    }

    uint numPlayers = atoi(argv[1]);
    if (numPlayers < 2 or numPlayers > 12) {
        usage(argv[0]);
    }

    Game game(numPlayers);
    game.play();

    return 0;
}

/*-----------------------------------------------------------*/

static void usage(char const *name)
{
    std::cout << "USAGE" << std::endl;
    std::cout << name << " <Num Players>" << std::endl;
    std::cout << std::endl;

    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "Classic Uno game, made in C++." << std::endl;
    std::cout << std::endl;

    std::cout << "OPTIONS" << std::endl;
    std::cout << "<Num Players>\tNumber of players in the game.";
    std::cout << " Must be between 2 and 12." << std::endl;
    std::cout << std::endl;

    exit(EXIT_FAILURE);
}
