#include <iostream>     // std::cout
#include <cstring>      // strcmp()
#include "offline.hpp"
#include "client.hpp"
#include "server.hpp"

// Shows how to use the program, leaving if afterwards
static void usage(char const *name);

/*-----------------------------------------------------------*/

int main(int argc, char const *argv[])
{
    if (argc < 3) {
        usage(argv[0]);
    }

    if (strcmp(argv[1], "-c") == 0) {
        unsigned short port = atoi(argv[2]);
        Client client("localhost", port);
    }

    if (strcmp(argv[1], "-s") == 0) {
        unsigned short port = atoi(argv[2]);
        Server server(port);
    }

    if (strcmp(argv[1], "-l") == 0) {
        uint numPlayers = atoi(argv[2]);
        if (numPlayers < 2 or numPlayers > 12) {
            usage(argv[0]);
        }
        Offline offline(numPlayers);
        offline.run();
    }

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
