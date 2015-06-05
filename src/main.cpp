#include <iostream>     // std::cout
#include <cstring>      // strcmp()
#include "offline.hpp"
#include "client.hpp"
#include "server.hpp"

// Asks user for name input
static std::string nameInput();

// Shows how to use the program, leaving if afterwards
static void usage(char const *name);

/*-----------------------------------------------------------*/

int main(int argc, char const *argv[])
{
    std::string name;

    if (argc < 3) {
        usage(argv[0]);
    }

    if (strcmp(argv[1], "-l") == 0) {
        uint numPlayers = atoi(argv[2]);
        if (numPlayers < 2 or numPlayers > 12) {
            usage(argv[0]);
        }
        Offline offline(numPlayers);
        offline.run();
    }

    else if (strcmp(argv[1], "-c") == 0) {
        if (argc < 4) {
            usage(argv[0]);
        }
        sf::IpAddress ip(argv[2]);
        unsigned short port = atoi(argv[3]);
        Client client(nameInput(), ip, port);
    }

    else if (strcmp(argv[1], "-s") == 0) {
        unsigned short port = atoi(argv[2]);
        
        Server server(nameInput(), port);
    }

    else {
        usage(argv[0]);
    }

    return 0;
}

/*-----------------------------------------------------------*/

static std::string nameInput()
{
    std::string name;

    std::cout << "Type in your name: ";
    std::cin  >> name;

    return name;
}

/*-----------------------------------------------------------*/

static void usage(char const *name)
{
    std::cout << "USAGE\n";
    std::cout << "\t" << name << " <-l PLAYERS> <-c IP PORT> <-s PORT> [-h]\n";
    std::cout << std::endl;

    std::cout << "DESCRIPTION\n";
    std::cout << "\tClassic Uno game, made in C++.\n";
    std::cout << "\tGames must always consist of 2 to 12 players.\n";
    std::cout << std::endl;

    std::cout << "MAIN OPTIONS\n";
    std::cout << "\t-l\tRuns local, offline game.\n";
    std::cout << "\t-c\tRuns program as client.\n";
    std::cout << "\t-s\tRuns program as server.\n";
    std::cout << "\t-h\tShows how to use the program, leaving it afterwards.\n";
    std::cout << std::endl;

    std::cout << "ADDITIONAL OPTIONS\n";
    std::cout << "\tIP\n\t\tIP of connecting server.\n";
    std::cout << "\tPORT\n\t\tServer's port number.\n";
    std::cout << "\tPLAYERS\n\t\tNumber of players in game.\n";

    exit(EXIT_FAILURE);
}
